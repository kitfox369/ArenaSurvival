// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ASGameMode.h"
#include "ASGameMode.h"

AASGameMode::AASGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaSurvival/Blueprint/BP_ASCharacterPlayer.BP_ASCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// Use unique path -> No include header -> Remove dependancy
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaSurvival.ASPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

}
