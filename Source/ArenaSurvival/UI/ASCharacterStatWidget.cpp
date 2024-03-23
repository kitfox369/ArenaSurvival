// Fill out your copyright notice in the Description page of Project Settings.


#include "ASCharacterStatWidget.h"
#include "Components/TextBlock.h"

void UASCharacterStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (TFieldIterator<FNumericProperty> PropIt(FASPlayerLevel::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());
		const FName TextBaseControlName = *FString::Printf(TEXT("Txt%sBase"), *PropIt->GetName());
		const FName TextModifierControlName = *FString::Printf(TEXT("Txt%sModifier"), *PropIt->GetName());

		UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextBaseControlName));
		if (BaseTextBlock)
		{
			BaseLookup.Add(PropKey, BaseTextBlock);
		}

		UTextBlock* ModifierTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextModifierControlName));
		if (ModifierTextBlock)
		{
			ModifierLookup.Add(PropKey, ModifierTextBlock);
		}
	}
	
	UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName("PlayerLevel"));
	if (BaseTextBlock)
	{
		PlayerLevel.Add("PlayerLevel", BaseTextBlock);
	}
}

void UASCharacterStatWidget::UpdateStat(const FASPlayerLevel& BaseStat, const FASPlayerLevel& ModifierStat)
{
	for (TFieldIterator<FNumericProperty> PropIt(FASPlayerLevel::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());

		float BaseData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&BaseStat, &BaseData);
		float ModifierData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&ModifierStat, &ModifierData);

		UTextBlock** BaseTextBlockPtr = BaseLookup.Find(PropKey);
		if (BaseTextBlockPtr)
		{
			(*BaseTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(BaseData)));
		}

		UTextBlock** ModifierTextBlockPtr = ModifierLookup.Find(PropKey);
		if (ModifierTextBlockPtr)
		{
			(*ModifierTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(ModifierData)));
		}
	}
}

void UASCharacterStatWidget::UpdateLevel(const float& CurrentLevel)
{
	UTextBlock** ModifierTextBlockPtr = PlayerLevel.Find("PlayerLevel");
	if (ModifierTextBlockPtr)
	{
		(*ModifierTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(CurrentLevel)));
	}
}
