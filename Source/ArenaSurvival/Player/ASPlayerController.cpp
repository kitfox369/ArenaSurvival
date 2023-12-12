// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ASPlayerController.h"

void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cursor put in Viewport
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}