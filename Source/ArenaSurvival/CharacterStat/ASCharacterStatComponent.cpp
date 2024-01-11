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
}


// Called when the game starts
void UASCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
	//SetHp(MaxHp);
}

void UASCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UASGameSingleton::Get().StageMaxLevel);
	SetBaseStat(UASGameSingleton::Get().GetStageStat(CurrentLevel)); 
	check(BaseStat.MaxHp > 0.0f);
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