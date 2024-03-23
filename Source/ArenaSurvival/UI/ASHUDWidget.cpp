// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASHUDWidget.h"
#include "Interface/ASCharacterHUDInterface.h"
#include "Interface/ASGimmickStateInterface.h"
#include "Character/ASCharacterBase.h"
#include "CharacterStat/ASCharacterStatComponent.h"
#include "ASHpBarWidget.h"
#include "ASExpBarWidget.h"
#include "ASStageStatusWidget.h"
#include "ASCharacterStatWidget.h"
#include "ASStartButtonWidget.h"
#include "Gimmick/ASStageGimmick.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

UASHUDWidget::UASHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UASHUDWidget::UpdateStat(const FASPlayerLevel& BaseStat, const FASPlayerLevel& ModifierStat)
{
	FASPlayerLevel TotalStat = BaseStat + ModifierStat;
	HpBar->SetMaxHp(TotalStat.MaxHp);
	ExpBar->SetMaxExp(TotalStat.RequireEXP);
	PlayerStat->SetMaxExp(TotalStat.RequireEXP);
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UASHUDWidget::UpdateLevel(const float& CurrentLevel)
{
	UE_LOG(LogTemp, Log, TEXT("UpdateLevel : %f"),CurrentLevel);
	CharacterStat->UpdateLevel(CurrentLevel);
}

void UASHUDWidget::UpdateStageStat(const FASStageLevel& StageLevel)
{
	StageStat->UpdateStageStatus(StageLevel);
}

void UASHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UASHUDWidget::UpdateExpBar(float InNewExp)
{
	if (PlayerStat->AddExp(InNewExp)) 
	{
		UpdateLevel(PlayerStat->GetCurrentLevel());
	}
	UE_LOG(LogTemp, Log, TEXT("UpdateExpBar : %f, %f"), PlayerStat->GetCurrentExp(), PlayerStat->GetMaxExp());
	ExpBar->UpdateExpBar(PlayerStat->GetCurrentExp());
}

void UASHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> ArrayOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AASStageGimmick::StaticClass(), ArrayOutActors);

	AASStageGimmick* StageGimmickSystem = Cast<AASStageGimmick>(ArrayOutActors[0]);
	ensure(StageGimmickSystem);

	GimmickObj = StageGimmickSystem;

	HpBar = Cast<UASHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	ExpBar = Cast<UASExpBarWidget>(GetWidgetFromName(TEXT("WidgetExpBar")));
	ensure(ExpBar);

	CharacterStat = Cast<UASCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	StageStat = Cast<UASStageStatusWidget>(GetWidgetFromName(TEXT("WidgetStageStat")));
	ensure(StageStat);

	StartButtonObj = Cast<UASStartButtonWidget>(GetWidgetFromName(TEXT("WidgetStartButton")));
	StartButtonObj->SetButtonFunction(GimmickObj);
	ensure(StartButtonObj);


	AASCharacterBase* BASEPawn = Cast<AASCharacterBase>(GetOwningPlayerPawn());
	PlayerStat = BASEPawn->GetStat();
	ensure(PlayerStat);

	// #MUST :  Change Status Text
	IASCharacterHUDInterface* HUDPawn = Cast<IASCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}

	IASGimmickStateInterface* HUDStagePawn = Cast<IASGimmickStateInterface>(GimmickObj);
	if (HUDStagePawn)
	{
		HUDStagePawn->SetupGimmickWidget(this);
	}

}
