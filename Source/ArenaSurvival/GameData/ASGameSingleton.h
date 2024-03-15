// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "ASStageStat.h"
#include "ASOpponentLevel.h"
#include "ASPlayerLevel.h"
#include "ASStageLevel.h"
#include "ASSpawnPosition.h"
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
	FORCEINLINE FASPlayerLevel GetPlayerLevel(int32 InLevel) const { return PlayerLevelTable.IsValidIndex(InLevel - 1) ? PlayerLevelTable[InLevel - 1] : FASPlayerLevel(); }
	FORCEINLINE FASOpponentLevel GetOpponentLevel(int32 InLevel) const { return OpponentLevelTable.IsValidIndex(InLevel - 1) ? OpponentLevelTable[InLevel - 1] : FASOpponentLevel(); }
	FORCEINLINE FASStageLevel GetStageLevel(int32 InLevel) const { return StageLevelTable.IsValidIndex(InLevel - 1) ? StageLevelTable[InLevel - 1] : FASStageLevel(); }
	FORCEINLINE FASSpawnPosition GetSpawnPosition(int32 InLevel) const { return SpawnPositionTable.IsValidIndex(InLevel - 1) ? SpawnPositionTable[InLevel - 1] : FASSpawnPosition(); }
	
	void GetSpawnPositions(TArray<FVector>& OutSpawnPositions);

	//FORCEINLINE FASStageStat GetStageStat(int32 InLevel) const { return StageStatTable.IsValidIndex(InLevel) ? StageStatTable[InLevel] : FASStageStat(); }

	UPROPERTY()
	int32 PlayerMaxLevel;
	UPROPERTY()
	int32 OpponentMaxLevel;
	UPROPERTY()
	int32 StageMaxLevel;
	UPROPERTY()
	int32 SpawnPositionMaxNum;

private:
	TArray<FASPlayerLevel> PlayerLevelTable;
	TArray<FASOpponentLevel> OpponentLevelTable;
	TArray<FASStageLevel> StageLevelTable;
	TArray<FASSpawnPosition> SpawnPositionTable;

	//TArray<FASStageStat> StageStatTable;
};
