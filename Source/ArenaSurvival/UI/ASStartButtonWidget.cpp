// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASStartButtonWidget.h"
#include "Gimmick/ASStageGimmick.h"
#include "Components/Button.h"

UASStartButtonWidget::UASStartButtonWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//static ConstructorHelpers::FClassFinder<UASHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaSurvival/UI/WBP_ASHUD.WBP_ASHUD_C"));
	//StageGimmickSystem = Cast(StaticLoadObject(AASStageGimmick::StaticClass(), NULL, TEXT("/Game/ArenaSurvival/UI/WBP_ASHUD.WBP_ASHUD_C")));
}

void UASStartButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton) {
		StartButton->OnClicked.AddDynamic(this, &UASStartButtonWidget::StartButtonOnClicked);
	}
}

void UASStartButtonWidget::StartButtonOnClicked()
{
	IASGimmickStateInterface* GimmickWidget = Cast<IASGimmickStateInterface>(GimmickObject.GetDefaultObject());
	ensure(GimmickWidget);
	if (GimmickWidget)
	{
		GimmickWidget->SetupGimmickState();
	}
}
