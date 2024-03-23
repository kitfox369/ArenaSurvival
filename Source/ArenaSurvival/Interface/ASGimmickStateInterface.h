// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASGimmickStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UASGimmickStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENASURVIVAL_API IASGimmickStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupGimmickWidget(class UASHUDWidget* InHUDWidget) = 0;
};
