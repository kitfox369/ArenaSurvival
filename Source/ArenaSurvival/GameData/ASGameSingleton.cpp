// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/ASGameSingleton.h"

DEFINE_LOG_CATEGORY(LogASGameSingleton);

UASGameSingleton::UASGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaSurvival/GameData/ASStageStatTable.ASStageStatTable'"));
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
	ensure(StageMaxLevel > 0);
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
