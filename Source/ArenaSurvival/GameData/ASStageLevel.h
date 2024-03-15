
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ASStageLevel.generated.h"

USTRUCT(BlueprintType)
struct FASStageLevel : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FASStageLevel() : MonsterID(0), MonsterNum(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MonsterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MonsterNum;

	FASStageLevel operator+(const FASStageLevel& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FASStageLevel Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FASStageLevel) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};