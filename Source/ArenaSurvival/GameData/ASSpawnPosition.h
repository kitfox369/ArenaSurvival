
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ASSpawnPosition.generated.h"

USTRUCT(BlueprintType)
struct FASSpawnPosition : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FASSpawnPosition() : X(0), Y(0), Z(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Z;

	FASSpawnPosition operator+(const FASSpawnPosition& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FASSpawnPosition Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FASSpawnPosition) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};