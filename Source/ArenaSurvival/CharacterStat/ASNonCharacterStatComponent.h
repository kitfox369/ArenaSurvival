// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ASStageStat.h"
#include "ASNonCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FASStageStat& /*BaseStat*/, const FASStageStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASURVIVAL_API UASNonCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASNonCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

	void SetLevelStat(int32 InNewLevel);
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void AddBaseStat(const FASStageStat& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetBaseStat(const FASStageStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FASStageStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FASStageStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FASStageStat& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE FASStageStat GetTotalStat() const { return BaseStat + ModifierStat; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE void HealHp(float InHealAmount) { CurrentHp = FMath::Clamp(CurrentHp + InHealAmount, 0, GetTotalStat().MaxHp); OnHpChanged.Broadcast(CurrentHp); }
	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }

	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	float ApplyDamage(float InDamage);
	
protected:
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FASStageStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FASStageStat ModifierStat;

};
