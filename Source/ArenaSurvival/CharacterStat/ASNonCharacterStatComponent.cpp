// Fill out your copyright notice in the Description page of Project Settings.


#include "ASNonCharacterStatComponent.h"
#include "GameData/ASGameSingleton.h"

// #MUST :  Apply Modifier along Stage Level
// Sets default values for this component's properties
UASNonCharacterStatComponent::UASNonCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;

	bWantsInitializeComponent = true;

	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}

void UASNonCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UASNonCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
}

float UASNonCharacterStatComponent::ApplyDamage(float InDamage)
{
	return 0.0f;
}

void UASNonCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

