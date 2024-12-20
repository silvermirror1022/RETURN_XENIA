﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/RXHUDWidget.h"
#include "UI/RXHpSetWidget.h"
#include "Interface/RXPlayerHUDInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/RXShieldCoolTimeWidget.h"

URXHUDWidget::URXHUDWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void URXHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//HpBar = Cast<URXHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	//ensure(HpBar);
	/*
		HUD는 GetOwningPlayer함수를 사용해서 HUD를 소유하는 컨트롤러를 가져올수있음.
		또는 GetOwningPlayerPawn함수를 통해서 컨트롤러가 빙의하고 있는 폰을 가져올수 있음.
	*/

	IRXPlayerHUDInterface* HUDPawn = Cast<IRXPlayerHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}

void URXHUDWidget::UpdateHpSet(int32 InHp,int32 InShield)
{
	HpSet->UpdateHpAndShield(InHp, InShield); //HpSet내부 함수그냥 그대로호출 , JUST PASS
	//HUD BP가 갖고 있는 RXHpSetWidget의 Update를 그대로 호출함. -> 변경된 Stat의 체력기반으로 HUD 업데이트
}

void URXHUDWidget::UpdateShieldCoolTime(bool HasSister)
{
	if (ShieldCoolTime && HasSister)
	{
		ShieldCoolTime->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ShieldCoolTime->SetVisibility(ESlateVisibility::Hidden);
	}
}
