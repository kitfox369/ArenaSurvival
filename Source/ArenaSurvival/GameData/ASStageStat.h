
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ASStageStat.generated.h"

USTRUCT(BlueprintType)
struct FASStageStat : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FASStageStat() : MaxHp(0.0f), Attack(0.0f), AttackRange(0.0f), AttackSpeed(0.0f), MonsterID(0.0f), MonsterNum(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MonsterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MonsterNum;

	FASStageStat operator+(const FASStageStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FASStageStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FASStageStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};