// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ASPlayerController.h"
#include "UI/ASHUDWidget.h"

AASPlayerController::AASPlayerController()
{
	static ConstructorHelpers::FClassFinder<UASHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaSurvival/UI/WBP_ASHUD.WBP_ASHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ASHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cursor put in Viewport
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	// Create ASHUDWidget
	ASHUDWidget = CreateWidget<UASHUDWidget>(this, ASHUDWidgetClass);
	if (ASHUDWidget)
	{
		ASHUDWidget->AddToViewport();
	}
}