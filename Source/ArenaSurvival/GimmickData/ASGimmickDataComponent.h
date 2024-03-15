// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ASStageLevel.h"
#include "GameData/ASSpawnPosition.h"
#include "ASGimmickDataComponent.generated.h"

DECLARE_DELEGATE(FOnStageClearDelegate);
USTRUCT(BlueprintType)
struct FOnStageClearDelegateWrapper
{
	GENERATED_BODY()
	
	FOnStageClearDelegateWrapper() { }
	FOnStageClearDelegateWrapper(const FOnStageClearDelegate& InDelegate) : StageDelegate(InDelegate) {}
	FOnStageClearDelegate StageDelegate;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASURVIVAL_API UASGimmickDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASGimmickDataComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnStageClearDelegateWrapper OnStageClear;

	void SetupGimmickData();
	void SetStageLevel(int32 InNewLevel);
	void GoNextStage();

	FORCEINLINE void SetStageData(const FASStageLevel& InStageLevel) { StageLevelData = InStageLevel; }
	FORCEINLINE void AddSpawnPosition(const FASSpawnPosition& InSpawnPosition) { SpawnPositions.Add(FVector(InSpawnPosition.X, InSpawnPosition.Y, InSpawnPosition.Z)); }
	FORCEINLINE void SetCurrentOpponentNum(const float InOpponentNum) { CurrentOpponentNum = InOpponentNum; }

	FORCEINLINE float GetCurrentStageLevel() const { return CurrentStageLevel; }
	FORCEINLINE float GetCurrentOpponentNum() const { return CurrentOpponentNum; }
	FORCEINLINE FASStageLevel GetStageData() const { return StageLevelData; }
	FORCEINLINE FVector GetSpawnPosition(uint16 InSpawnIndex) const { return SpawnPositions[InSpawnIndex]; }
	FORCEINLINE FVector GetRandomSpawnPosition() const { uint16 RandomIndex = FMath::RandRange(0, SpawnPositions.Num() - 1); return SpawnPositions[RandomIndex]; }

	FORCEINLINE void DeadOpponent();

	// Info
protected:
	UPROPERTY(VisibleInstanceOnly, Category = Opponent)
	float CurrentStageLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Opponent)
	uint32 CurrentOpponentNum;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Opponent, Meta = (AllowPrivateAccess = "true"))
	FASStageLevel StageLevelData;

	UPROPERTY(VisibleInstanceOnly, Category = Opponent)
	TArray<FVector> SpawnPositions;
};
