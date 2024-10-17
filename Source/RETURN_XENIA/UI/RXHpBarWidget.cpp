// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Player/RXPlayerStatComponent.h" 


URXHpBarWidget::URXHpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void URXHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);

	AActor* Owner = GetOwningPlayerPawn();
	if (Owner)
	{
		URXPlayerStatComponent* StatComponent = Owner->FindComponentByClass<URXPlayerStatComponent>();
		if (StatComponent)
		{
			MaxHp = StatComponent->GetMaxHp();
		}
	}
}

void URXHpBarWidget::UpdateHpBar(float NewCurrentHp)
{

	CurrentHp = NewCurrentHp;

	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}
}