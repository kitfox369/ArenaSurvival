// Fill out your copyright notice in the Description page of Project Settings.


#include "ASWidgetComponent.h"
#include "UI/ASUserWidget.h"

void UASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UASUserWidget* ASUserWidget = Cast<UASUserWidget>(GetWidget());
	if (ASUserWidget)
	{
		ASUserWidget->SetOwningActor(GetOwner());
	}
}