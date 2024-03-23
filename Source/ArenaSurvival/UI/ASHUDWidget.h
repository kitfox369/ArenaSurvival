// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ASStageStat.h"
#include "GameData/ASStageLevel.h"
#include "GameData/ASPlayerLevel.h"
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
	void UpdateStat(const FASPlayerLevel& BaseStat, const FASPlayerLevel& ModifierStat);
	void UpdateLevel(const float& CurrentLevel);
	void UpdateStageStat(const FASStageLevel& StageLevel);
	void UpdateHpBar(float NewCurrentHp);
	void UpdateExpBar(float InNewExp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UASHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UASExpBarWidget> ExpBar;

	UPROPERTY()
	TObjectPtr<class UASCharacterStatWidget> CharacterStat;

	UPROPERTY()
	TObjectPtr<class UASStageStatusWidget> StageStat;

	UPROPERTY()
	TObjectPtr<class UASStartButtonWidget> StartButtonObj;

	UPROPERTY()
	TObjectPtr<class AASStageGimmick> GimmickObj;

	//Player Stat
protected:
	TObjectPtr<class UASCharacterStatComponent> PlayerStat;

};
