// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ASPlayerLevel.h"
#include "ASCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnExpChangedDelegate, float /*CurrentExp*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelChangedDelegate,const float& /*CurrentLevel*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FASPlayerLevel& /*BaseStat*/, const FASPlayerLevel& /*ModifierStat*/);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENASURVIVAL_API UASCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
	// Sets default values for this component's properties
	UASCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnExpChangedDelegate OnExpChanged;
	FOnStatChangedDelegate OnStatChanged;
	FOnLevelChangedDelegate OnLevelChanged;


	void SetLevelStat(int32 InNewLevel);
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void AddBaseStat(const FASPlayerLevel& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetBaseStat(const FASPlayerLevel& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FASPlayerLevel& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FASPlayerLevel& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FASPlayerLevel& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE FASPlayerLevel GetTotalStat() const { return BaseStat + ModifierStat; }

	FORCEINLINE float GetMaxExp() { return MaxExp; }
	FORCEINLINE void SetMaxExp(float InMaxExp){MaxExp= InMaxExp;}
	FORCEINLINE float GetCurrentExp() const { return CurrentExp; }
	bool  AddExp(float InAddExpAmount);

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

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentExp;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FASPlayerLevel BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FASPlayerLevel ModifierStat;
};