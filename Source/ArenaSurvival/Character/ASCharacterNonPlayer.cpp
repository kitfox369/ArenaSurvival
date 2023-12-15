// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASCharacterNonPlayer.h"

AASCharacterNonPlayer::AASCharacterNonPlayer()
{
}

void AASCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}