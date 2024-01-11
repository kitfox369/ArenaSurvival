// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASHUDWidget.h"
#include "Interface/ASCharacterHUDInterface.h"
#include "Interface/ASGimmickStateInterface.h"
#include "ASHpBarWidget.h"
#include "ASStageStatusWidget.h"
#include "ASStartButtonWidget.h"
#include "Gimmick/ASStageGimmick.h"
#include "Kismet/GameplayStatics.h"

UASHUDWidget::UASHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UASHUDWidget::UpdateStat(const FASStageStat& BaseStat, const FASStageStat& ModifierStat)
{
}

void UASHUDWidget::UpdateHpBar(float NewCurrentHp)
{
}

void UASHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UASHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UASStageStatusWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	StartButtonObj = Cast<UASStartButtonWidget>(GetWidgetFromName(TEXT("WidgetStartButton")));
	ensure(StartButtonObj);


	// #MUST :  Change Status Text
	IASCharacterHUDInterface* HUDPawn = Cast<IASCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		//HUDPawn->SetupHUDWidget(this);
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AASStageGimmick::StaticClass(), ArrayOutActors);
	if (ArrayOutActors.Num() > 0)
	{
		AASStageGimmick* StageGimmickSystem = Cast<AASStageGimmick>(ArrayOutActors[0]);
		StartButtonObj->GimmickObject = StageGimmickSystem->GetClass();
	}
	
}
