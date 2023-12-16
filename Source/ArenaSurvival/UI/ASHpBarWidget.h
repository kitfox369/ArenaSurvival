// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASUserWidget.h"
#include "ASHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASHpBarWidget : public UASUserWidget
{
	GENERATED_BODY()
	
	public:
		UASHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
