// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASUserWidget.h"
#include "ASExpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASExpBarWidget : public UASUserWidget
{
	GENERATED_BODY()
public:
	UASExpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxExp(float NewMaxExp) { MaxExp = NewMaxExp; }
	void UpdateExpBar(float NewCurrentExp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> ExpProgressBar;

	UPROPERTY()
	float MaxExp;
};
