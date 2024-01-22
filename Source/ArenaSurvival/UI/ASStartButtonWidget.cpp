﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASStartButtonWidget.h"
#include "Gimmick/ASStageGimmick.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/ASGimmickStateInterface.h"
#include "Components/Button.h"

UASStartButtonWidget::UASStartButtonWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//static ConstructorHelpers::FClassFinder<UASHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaSurvival/UI/WBP_ASHUD.WBP_ASHUD_C"));
	//StageGimmickSystem = Cast(StaticLoadObject(AASStageGimmick::StaticClass(), NULL, TEXT("/Game/ArenaSurvival/UI/WBP_ASHUD.WBP_ASHUD_C")));
}

void UASStartButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton) 
	{
		StartButton->OnClicked.AddDynamic(this, &UASStartButtonWidget::StartButtonOnClicked);
	}
}

void UASStartButtonWidget::StartButtonOnClicked()
{
	// SONNY : Button 클래스와 Gimmick 간의 의존성 문제
	// Button은 OwiningActor가 따로 존재하지 않음 (굳이 따지자면 GameMode)
	// 그렇다면, Gimmick에서 찾아서 바로 Stage 시작 하는 것도 나쁘진 않을 듯 함 (찾고, 클래스 검증을 해야하기 때문에 헤더파일 의존성이 생기긴 함)
	// Only Using Start Timing -> (HUD로 저장해서 우회할 필요 없이 한번 만
	TArray<AActor*> ArrayOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AASStageGimmick::StaticClass(), ArrayOutActors);
	if (ArrayOutActors.Num() > 0)
	{
		AASStageGimmick* StageGimmickSystem = Cast<AASStageGimmick>(ArrayOutActors[0]);
		ensure(StageGimmickSystem);
		
		//StageGimmickSystem->SetupGimmickState();  // directly 사용

		// interface로 우회해서 사용 (일단은 놔둠)
		IASGimmickStateInterface* GimmickWidget = Cast<IASGimmickStateInterface>(StageGimmickSystem);
		ensure(GimmickWidget);
		if (GimmickWidget)
		{
			GimmickWidget->SetupGimmickState();
		}
	}
}
