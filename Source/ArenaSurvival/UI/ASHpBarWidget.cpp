#include "UI/ASHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/ASCharacterWidgetInterface.h"

UASHpBarWidget::UASHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UASHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);

	IASCharacterWidgetInterface* CharacterWidget = Cast<IASCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UASHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)  // If want to use ProgressBar ->  Must Add "UMG" Module in Build.cs 
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}