// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ASStageLevel.h"
#include "ASStageStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASStageStatusWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStageStatus(const FASStageLevel& StageLevel);
	
private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

};
