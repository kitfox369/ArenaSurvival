// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASUserWidget.h"
// SONNY : AASStageGimmick.h 지움 (전방 선언이기 떄문에 필요 없음)
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

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable,Category="Gimmick")
	void StartButtonOnClicked();
};
