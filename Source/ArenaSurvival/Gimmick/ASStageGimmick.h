// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ASGimmickStateInterface.h"
#include "ASStageGimmick.generated.h"

DECLARE_DELEGATE(FOnStageChangedDelegate);
USTRUCT(BlueprintType)
struct FStageChangedDelegateWrapper
{
	GENERATED_BODY()
	FStageChangedDelegateWrapper() { }
	FStageChangedDelegateWrapper(const FOnStageChangedDelegate& InDelegate) : StageDelegate(InDelegate) {}
	FOnStageChangedDelegate StageDelegate;
};

UENUM(BlueprintType)
enum class EStageState : uint8
{
	READY = 0,
	FIGHT,
	REWARD,
	NEXT
};

UCLASS()
class ARENASURVIVAL_API AASStageGimmick : public AActor, public IASGimmickStateInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASStageGimmick();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Stage Section
protected:
	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Stage;

	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> StageTrigger;

// Gate Section
protected:
	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;

	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	// State Section
protected:
	UPROPERTY(EditAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	EStageState CurrentState;

	void SetState(EStageState InNewState);

	UPROPERTY()
	TMap<EStageState, FStageChangedDelegateWrapper> StateChangeActions;

	void SetReady();

	UFUNCTION()
	void SetFight();

	void SetChooseReward();
	void SetChooseNext();

	// Fight Section
protected:
	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AASCharacterNonPlayer> OpponentClass;

	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	float OpponentSpawnTime;

	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	float FightModeTime;

	UFUNCTION()
	void OnOpponentDestroyed(AActor* DestroyedActor);

	FTimerHandle OpponentTimerHandle;
	void OnOpponentSpawn();

	void SetupGimmickState()override;

public:

	FTimerHandle FightTimerHandle;
	void OnFightMode();

	// Reward Section
protected:
	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AASItemBox> RewardBoxClass;

	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<class AASItemBox>> RewardBoxes;

	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TMap<FName, FVector> RewardBoxLocations;

	UFUNCTION()
	void OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnRewardBoxes();

	// Stage Stat
protected:
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentStageNum;
};
