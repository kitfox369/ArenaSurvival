// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ASStageStat.h"
#include "ASHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UASHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FASStageStat& BaseStat, const FASStageStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UASHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UASStageStatusWidget> CharacterStat;

	UPROPERTY()
	TObjectPtr<class UASStartButtonWidget> StartButtonObj;

	TArray<AActor*> ArrayOutActors;

};
