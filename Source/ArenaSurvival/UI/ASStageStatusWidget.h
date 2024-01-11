// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASUserWidget.h"
#include "ASStageStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASStageStatusWidget : public UASUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStageStatus(float StageNumber);
	
private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

};
