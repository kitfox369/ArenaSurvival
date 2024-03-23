#include "GimmickData/ASGimmickDataComponent.h"
#include "GameData/ASGameSingleton.h"
#include "UI/ASHUDWidget.h"

// Sets default values for this component's properties
UASGimmickDataComponent::UASGimmickDataComponent()
{
	CurrentStageLevel = 1;
	CurrentOpponentNum = 0;
	
	bWantsInitializeComponent = true;
}

void UASGimmickDataComponent::InitializeComponent()
{
	Super::InitializeComponent();

	StageLevelData = UASGameSingleton::Get().GetStageLevel(CurrentStageLevel);

	// OutSpawnPosition
	UASGameSingleton::Get().GetSpawnPositions(SpawnPositions);

	UE_LOG(LogTemp, Log, TEXT("MonsterNum : %f"), StageLevelData.MonsterNum);
}

void UASGimmickDataComponent::SetupGimmickData()
{
	StageLevelData = UASGameSingleton::Get().GetStageLevel(CurrentStageLevel);
	UASGameSingleton::Get().GetSpawnPositions(SpawnPositions);
}

void UASGimmickDataComponent::SetStageLevel(int32 InNewLevel)
{
	// #MUST : CurrentStageLevel 과 StageLevelData.StageLevel 통합 필요
	CurrentStageLevel = InNewLevel;
	StageLevelData = UASGameSingleton::Get().GetStageLevel(CurrentStageLevel);
}

void UASGimmickDataComponent::GoNextStage()
{
	SetStageLevel(CurrentStageLevel + 1);
}

void UASGimmickDataComponent::DeadOpponent()
{
	CurrentOpponentNum--;

	//Exp Up : 50은 임의의 수
	HUDWidget->UpdateExpBar(50);

	if (CurrentOpponentNum <= 0)
	{
		OnStageClear.Broadcast();
	}
}
