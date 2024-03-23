// Fill out your copyright notice in the Description page of Project Settings.


#include "ASStageStatusWidget.h"
#include "Components/TextBlock.h"

void UASStageStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (TFieldIterator<FNumericProperty> PropIt(FASStageLevel::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());
		const FName TextBaseControlName = *FString::Printf(TEXT("Txt%s"), *PropIt->GetName());

		UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextBaseControlName));
		if (BaseTextBlock)
		{
			BaseLookup.Add(PropKey, BaseTextBlock);
		}
	}
}

void UASStageStatusWidget::UpdateStageStatus(const FASStageLevel& StageLevel)
{
	
	for (TFieldIterator<FNumericProperty> PropIt(FASStageLevel::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());

		float BaseData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&StageLevel, &BaseData);

		UTextBlock** BaseTextBlockPtr = BaseLookup.Find(PropKey);
		if (BaseTextBlockPtr)
		{
			(*BaseTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(BaseData)));
		}
	}
}
 