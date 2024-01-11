// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASStageStatusWidget.h"
#include "Components/TextBlock.h"

void UASStageStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*for (TFieldIterator<FNumericProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());
		const FName TextBaseControlName = *FString::Printf(TEXT("Txt%sBase"), *PropIt->GetName());
		const FName TextModifierControlName = *FString::Printf(TEXT("Txt%sModifier"), *PropIt->GetName());

		UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextBaseControlName));
		if (BaseTextBlock)
		{
			BaseLookup.Add(PropKey, BaseTextBlock);
		}
	}*/
}

void UASStageStatusWidget::UpdateStageStatus(float StageNumber)
{
	ensure(StageNumber >= 0);
}
 