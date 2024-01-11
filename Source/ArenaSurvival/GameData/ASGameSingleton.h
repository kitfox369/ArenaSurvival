// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ASStageStat.h"
#include "ASGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogASGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class ARENASURVIVAL_API UASGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UASGameSingleton();
	
	static UASGameSingleton& Get();

public:
	FORCEINLINE FASStageStat GetStageStat(int32 InLevel) const { return StageStatTable.IsValidIndex(InLevel) ? StageStatTable[InLevel] : FASStageStat(); }

	UPROPERTY()
	int32 StageMaxLevel;

private:
	TArray<FASStageStat> StageStatTable;

};
