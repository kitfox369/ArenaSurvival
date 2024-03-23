// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ASCharacterStatComponent.h"
#include "GameData/ASGameSingleton.h"

// Sets default values for this component's properties
UASCharacterStatComponent::UASCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;

	bWantsInitializeComponent = true;

	MaxHp = 200.0f;
	CurrentHp = MaxHp;
	MaxExp = 200.0f;
	CurrentExp = 0.0f;
}


// Called when the game starts
void UASCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	MaxHp = BaseStat.MaxHp;
	SetHp(BaseStat.MaxHp);
	MaxExp = 200;
	CurrentExp = 0;
	//SetHp(MaxHp);
}

void UASCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UASGameSingleton::Get().PlayerMaxLevel);
	SetBaseStat(UASGameSingleton::Get().GetPlayerLevel(CurrentLevel)); 
	check(BaseStat.MaxHp > 0.0f);
}

bool UASCharacterStatComponent::AddExp(float InAddExpAmount)
{
	if (CurrentExp + InAddExpAmount >= MaxExp) 
	{
		CurrentExp = 0;
		CurrentLevel += 1;
		return true;
	}
	else 
	{
		CurrentExp += InAddExpAmount;
		return false;
	}
}

float UASCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UASCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}