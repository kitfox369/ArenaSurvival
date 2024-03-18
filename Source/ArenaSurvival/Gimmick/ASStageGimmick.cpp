// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ASStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Physics/ASCollision.h"
#include "Character/ASCharacterNonPlayer.h"
#include "UI/ASWidgetComponent.h"
#include "UI/ASStartButtonWidget.h"
#include "Item/ASItemBox.h"
#include "GimmickData/ASGimmickDataComponent.h"

// Sets default values
AASStageGimmick::AASStageGimmick()
{
	// Stage Section
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));
	RootComponent = Stage;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaSurvival/Environment/Stage/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshRef.Object)
	{
		Stage->SetStaticMesh(StageMeshRef.Object);
	}

	StageTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger->SetBoxExtent(FVector(1350.0, 1350.0f, 400.0f));
	StageTrigger->SetupAttachment(Stage);
	StageTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 440.0f));
	StageTrigger->SetCollisionProfileName(CPROFILE_ASTRIGGER);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Asian_Village/meshes/building/SM_roof_08.SM_roof_08'"));
	// Reward Section  #MUST : Currently Reward Spawning is relative gate
	static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };
	for (FName GateSocket : GateSockets)
	{
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		Gate->SetStaticMesh(GateMeshRef.Object);
		Gate->SetupAttachment(Stage, GateSocket);
		Gate->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Gate->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Gates.Add(GateSocket, Gate);
	}

	// Fight Section
	OpponentSpawnTime = 2.0f;
	OpponentClass = AASCharacterNonPlayer::StaticClass();

	FightModeTime = 3.0f;

	RewardBoxClass = AASItemBox::StaticClass();
	for (FName GateSocket : GateSockets)
	{
		FVector BoxLocation = Stage->GetSocketLocation(GateSocket) / 2;
		RewardBoxLocations.Add(GateSocket, BoxLocation);
	}

	// Data
	GimmickData = CreateDefaultSubobject<UASGimmickDataComponent>(TEXT("StageData"));
}

void AASStageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AASStageGimmick::BeginPlay()
{
	Super::BeginPlay();

	// State Section ( InitializeComponent -> BeginPlay() )
	CurrentState = EStageState::READY;
	StateChangeActions.Add(EStageState::READY, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AASStageGimmick::SetReady)));
	StateChangeActions.Add(EStageState::FIGHT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AASStageGimmick::SetFight)));
	StateChangeActions.Add(EStageState::REWARD, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AASStageGimmick::SetChooseReward)));
	StateChangeActions.Add(EStageState::NEXT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AASStageGimmick::SetChooseNext)));
	SetState(CurrentState);

	SetupGimmickState();

	GimmickData->OnStageClear.AddUObject(this, &AASStageGimmick::SetChooseReward);
}

void AASStageGimmick::SetState(EStageState InNewState)
{
	CurrentState = InNewState;

	if (StateChangeActions.Contains(InNewState))
	{
		// IfBound -> ensure not null
		StateChangeActions[CurrentState].StageDelegate.ExecuteIfBound();
	}
}

void AASStageGimmick::SetReady()
{
	StageTrigger->SetCollisionProfileName(CPROFILE_ASTRIGGER);
}

void AASStageGimmick::SetFight()
{
	UE_LOG(LogTemp, Log, TEXT("CurrentStage : %f"), GimmickData->GetCurrentStageLevel());

	GWorld->GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(OpponentTimerHandle, this, &AASStageGimmick::OnOpponentSpawn, OpponentSpawnTime, false);
}

void AASStageGimmick::SetChooseReward()
{
	SpawnRewardBoxes();
}

void AASStageGimmick::SetChooseNext()
{
	GimmickData->GoNextStage();

	GWorld->GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(FightTimerHandle, this, &AASStageGimmick::OnFightMode, FightModeTime, false);
}

void AASStageGimmick::OnOpponentDestroyed(AActor* DestroyedActor)
{
	GimmickData->DeadOpponent();
}

void AASStageGimmick::OnOpponentSpawn()
{
	const uint16 MonsterNum = GimmickData->GetStageData().MonsterNum;

	for (uint16 i = 0; i < MonsterNum; i++)
	{
		const FVector SpawnLocation = GimmickData->GetRandomSpawnPosition();

		// Avoid Overlap
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		bool bHit = GetWorld()->SweepSingleByChannel(HitResult, SpawnLocation, SpawnLocation, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(100), CollisionParams);

		if (bHit)
		{
			//UE_LOG(LogTemp, Log, TEXT("Hit!"));
			i--;
			continue;
		}

		AActor* OpponentActor = GWorld->GetGameInstance()->GetWorld()->SpawnActor(OpponentClass, &SpawnLocation, &FRotator::ZeroRotator);
		AASCharacterNonPlayer* ASOpponentCharacter = Cast<AASCharacterNonPlayer>(OpponentActor);
		if (ASOpponentCharacter)
		{
			ASOpponentCharacter->OnDestroyed.AddDynamic(this, &AASStageGimmick::OnOpponentDestroyed);
		}
	}
	
	GimmickData->SetCurrentOpponentNum(MonsterNum);
}

void AASStageGimmick::SetupGimmickState()
{
	if (GimmickData->GetCurrentOpponentNum() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("There are Opponents yet : %d"), GimmickData->GetCurrentOpponentNum());
		return;
	}

	SetState(EStageState::FIGHT);
}

void AASStageGimmick::OnFightMode()
{
	SetState(EStageState::FIGHT);
}

void AASStageGimmick::OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			AASItemBox* ValidItemBox = RewardBox.Get();
			AActor* OverlappedBox = OverlappedComponent->GetOwner();
			if (OverlappedBox != ValidItemBox)
			{
				ValidItemBox->Destroy();
			}
		}
	}

	SetState(EStageState::NEXT);
}

void AASStageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocation : RewardBoxLocations)
	{
		FVector WorldSpawnLocation = GetActorLocation() + RewardBoxLocation.Value + FVector(0.0f, 0.0f, 0.0f);
		AActor* ItemActor = GWorld->GetGameInstance()->GetWorld()->SpawnActor(RewardBoxClass, &WorldSpawnLocation, &FRotator::ZeroRotator);
		AASItemBox* RewardBoxActor = Cast<AASItemBox>(ItemActor);

		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLocation.Key);
			RewardBoxActor->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &AASStageGimmick::OnRewardTriggerBeginOverlap);
			RewardBoxes.Add(RewardBoxActor);
		}
	}

	//bHasFinishedSpawning = true, handler error occur (reusable)
	/*for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
		}
	}*/
}