// Fill out your copyright notice in the Description page of Project Settings.


#include "ASExpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/ASCharacterWidgetInterface.h"

UASExpBarWidget::UASExpBarWidget(const FObjectInitializer& ObjectInitializer)
{
	MaxExp = -1.0f;
}

void UASExpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbExpBar")));
	ensure(ExpProgressBar);

	IASCharacterWidgetInterface* CharacterWidget = Cast<IASCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UASExpBarWidget::UpdateExpBar(float NewCurrentExp)
{
	if (ExpProgressBar)  // If want to use ProgressBar ->  Must Add "UMG" Module in Build.cs 
	{
		ExpProgressBar->SetPercent(NewCurrentExp / MaxExp);
	}
}
