// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASUserWidget.h"
#include "Gimmick/ASStageGimmick.h"
#include "ASStartButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASStartButtonWidget : public UASUserWidget
{
	GENERATED_BODY()
public:
	UASStartButtonWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	class UButton* StartButton;

	virtual void NativeConstruct()override;

public:
	UFUNCTION(BlueprintCallable,Category="Gimmick")
	void StartButtonOnClicked();

	TSubclassOf<class AASStageGimmick> GimmickObject;

};
