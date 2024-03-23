// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ASPlayerLevel.h"
#include "ASCharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

	protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FASPlayerLevel& BaseStat, const FASPlayerLevel& ModifierStat);

	void UpdateLevel(const float& CurrentLevel);

private:
	// 확장성을 위한 TMap으로 선언
	UPROPERTY()
	TMap<FName, class UTextBlock*> PlayerLevel;

	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookup;
};
