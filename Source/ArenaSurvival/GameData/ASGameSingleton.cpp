// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/ASGameSingleton.h"

DEFINE_LOG_CATEGORY(LogASGameSingleton);

UASGameSingleton::UASGameSingleton()
{
	// Player
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerDataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASPlayerLevelTable.ASPlayerLevelTable'"));
	if (nullptr != PlayerDataTableRef.Object)
	{
		const UDataTable* DataTable = PlayerDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, PlayerLevelTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FASPlayerLevel*>(Value);
			}
		);
	}

	PlayerMaxLevel = PlayerLevelTable.Num();
	ensure(PlayerMaxLevel > 0);
	
	// Opponent
	static ConstructorHelpers::FObjectFinder<UDataTable> OpponentDataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASOpponentLevelTable.ASOpponentLevelTable'"));
	if (nullptr != OpponentDataTableRef.Object)
	{
		const UDataTable* DataTable = OpponentDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, OpponentLevelTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FASOpponentLevel*>(Value);
			}
		);
	}

	OpponentMaxLevel = OpponentLevelTable.Num();
	ensure(OpponentMaxLevel > 0);
	
	// Stage Info
	static ConstructorHelpers::FObjectFinder<UDataTable> StageDataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASStageLevelTable.ASStageLevelTable'"));
	if (nullptr != StageDataTableRef.Object)
	{
		const UDataTable* DataTable = StageDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, StageLevelTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FASStageLevel*>(Value);
			}
		);
	}

	StageMaxLevel = StageLevelTable.Num();
	ensure(StageMaxLevel > 0); 
	
	// Spawn Position
	static ConstructorHelpers::FObjectFinder<UDataTable> SpawnDataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASSpawnPositionTable.ASSpawnPositionTable'"));
	if (nullptr != SpawnDataTableRef.Object)
	{
		const UDataTable* DataTable = SpawnDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, SpawnPositionTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FASSpawnPosition*>(Value);
			}
		);
	}

	SpawnPositionMaxNum = SpawnPositionTable.Num();
	ensure(SpawnPositionMaxNum > 0);

	/*static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASStageStatTable.ASStageStatTable'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, StageStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FASStageStat*>(Value);
			}
		);
	}

	StageMaxLevel = StageStatTable.Num();
	ensure(StageMaxLevel > 0);*/
}

UASGameSingleton& UASGameSingleton::Get()
{
	UASGameSingleton* Singleton = CastChecked<UASGameSingleton>(GEngine->GameSingleton);
	if (Singleton) 
	{
		return *Singleton;
	}

	UE_LOG(LogASGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UASGameSingleton>();
}

void UASGameSingleton::GetSpawnPositions(TArray<FVector>& OutSpawnPositions)
{
	for (uint16 i = 1; i < SpawnPositionMaxNum + 1; i++)
	{
		FASSpawnPosition SpawnPosition = GetSpawnPosition(i);
		FVector Position = FVector(SpawnPosition.X, SpawnPosition.Y, SpawnPosition.Z);
		
		OutSpawnPositions.Add(Position);
	}
}
