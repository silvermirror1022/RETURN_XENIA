// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXHpSetWidget.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Player/RXPlayerStatComponent.h" 


URXHpSetWidget::URXHpSetWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void URXHpSetWidget::NativeConstruct()
{
	Super::NativeConstruct();


	AActor* Owner = GetOwningPlayerPawn();
	if (Owner)
	{
        PlayerStatComp = Owner->FindComponentByClass<URXPlayerStatComponent>();
		if (PlayerStatComp)
		{
			CurrentHpCnt = PlayerStatComp->GetCurrentHp();
			CurrentShieldCnt = PlayerStatComp->GetCurrentShield();

			// 델리게이트 연결
            PlayerStatComp->OnPlayerHpAndShieldChanged.AddUObject(this, &URXHpSetWidget::UpdateHpAndShield);

			// 초기 위젯 세팅
			UpdateHpAndShield(CurrentHpCnt, CurrentShieldCnt);
		}
	}
}

void URXHpSetWidget::UpdateHpAndShield(int32 InCurrentHp,int32 InCurrentShield)
{
	CurrentHpCnt = InCurrentHp;
	CurrentShieldCnt = InCurrentShield;

    if (!HorizontalBox) return;

    HorizontalBox->ClearChildren(); //기존 위젯들 삭제

    // HpWidgetClass 기반 위젯 생성 및 추가
    for (int32 i = 0; i < CurrentHpCnt; ++i)
    {
        if (HpWidgetClass)
        {
            UE_LOG(LogTemp, Log, TEXT("Creating Widget %d"), i);
            UUserWidget* HpWidget = CreateWidget<UUserWidget>(GetWorld(), HpWidgetClass);
            if (HpWidget)
            {
                HorizontalBox->AddChild(HpWidget);
            }
        }
    }

    // ShieldWidgetClass 기반 위젯 생성 및 추가
    for (int32 i = 0; i < CurrentShieldCnt; ++i)
    {  
        if (ShieldWidgetClass&& PlayerStatComp->bHasShield)
        {
            UUserWidget* ShieldWidget = CreateWidget<UUserWidget>(GetWorld(), ShieldWidgetClass);
            if (ShieldWidget)
            {
                HorizontalBox->AddChild(ShieldWidget);
            }
        }
    }
}