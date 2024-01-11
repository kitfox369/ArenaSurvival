// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ARENASURVIVAL_API AASPlayerController : public APlayerController
{
	GENERATED_BODY() 

public:
	AASPlayerController();

protected:
	virtual void BeginPlay() override;


//HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UASHUDWidget> ASHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UASHUDWidget> ASHUDWidget;
};