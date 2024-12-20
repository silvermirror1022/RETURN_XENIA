﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RXPlayerStatComponent.h"
#include "System/RXGameInstance.h"
#include "RXDebugHelper.h"

URXPlayerStatComponent::URXPlayerStatComponent()
{
	MaxShield = 1;
	MaxHp = 3;
	bIsShieldRegenActive = false;
	bWantsInitializeComponent = true; //InitializeComponent 함수 호출을 위해

	PrimaryComponentTick.bCanEverTick = true; // 틱 활성화
	PrimaryComponentTick.bStartWithTickEnabled = true; 
}

void URXPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if (GetGameInstance())
	{
		CurrentHp = GI->GetGI_Hp();
		CurrentShield = GI->GetGI_Shield();
	}
}

void URXPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false); 

	if (GetGameInstance())
	{
		if (GI->IsProfileStatusAcquired("Sister"))
		{
			bHasShield = true;
			SetComponentTickEnabled(true); // 틱 활성화

			if(CurrentShield == 0) StartShieldRegen();
		}
		else
		{
			bHasShield = false;
		}
		CurrentHp = GI->GetGI_Hp();
		CurrentShield = GI->GetGI_Shield();
		if (OnPlayerHpAndShieldChanged.IsBound())
		{
			OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
		}
	}
}
void URXPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShieldRegenTimer.IsValid())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(ShieldRegenTimer);

		int32 CurrentSecIndex = FMath::Clamp(static_cast<int32>(8.0f-RemainingTime), 1, 8);
		//D(FString::Printf(TEXT("Current cooltime: %d"), CurrentSecIndex));
		// 델리게이트 호출로 UI 업데이트
		OnPlayerShieldSecRegenChanged.Broadcast(CurrentSecIndex);
	}
}
URXGameInstance* URXPlayerStatComponent::GetGameInstance()
{
	if (!GI)
	{
		GI = Cast<URXGameInstance>(GetWorld()->GetGameInstance());
		if (!GI)
		{
			UE_LOG(LogTemp, Error, TEXT("RXGameInstance is still null!"));
		}
	}
	return GI;
}
void URXPlayerStatComponent::SetHpToGI(int32 NewHp)
{
	CurrentHp = NewHp;
	GI->SetGI_Hp(NewHp);
    OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
}
void URXPlayerStatComponent::SetShieldToGI(int32 NewShield)
{
	CurrentShield = NewShield;
	GI->SetGI_Shield(NewShield);
    OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
}

void URXPlayerStatComponent::ApplyDamage(int32 InDamage)
{
	// 플레이어가 데미지를 입었을 때 호출
	if (bIsShieldRegenActive)
	{
		// 기존 쉴드 리젠 타이머 초기화
		GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTimer);
		bIsShieldRegenActive = false;
	}

	int32 DamageLeft = InDamage;

	// 쉴드가 있는 경우
	if (bHasShield && CurrentShield > 0)
	{
		const int32 ShieldDamage = FMath::Min(DamageLeft, CurrentShield);
		SetShieldToGI(CurrentShield - ShieldDamage); // 쉴드 감소
		DamageLeft -= ShieldDamage;
	}

	// 남은 데미지를 체력에 적용
	if (DamageLeft > 0)
	{
		SetHpToGI(CurrentHp - DamageLeft);
		OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);

		// 체력이 0 이하가 되면 델리게이트 호출
		if (CurrentHp <= 0)
		{
			OnPlayerHpZero.Broadcast();
		}
	}

	// 쉴드 리젠 처리
	if (bHasShield && CurrentShield == 0 && !bIsShieldRegenActive)
	{
		StartShieldRegen();
	}
}
void URXPlayerStatComponent::ApplyHealing(int32 InHealAmount)
{
	// 체력 회복
	if (InHealAmount > 0)
	{
		int32 NewHp = FMath::Clamp(CurrentHp + InHealAmount, 0, MaxHp); // 최대 HP 초과 방지
		SetHpToGI(NewHp);
	}

	// 여동생 방패가 있을 경우 방패 100% 회복
	if (bHasShield)
	{
		SetShieldToGI(MaxShield); // 방패를 최대치로 설정
	}

	GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTimer);
	OnPlayerShieldFull.Broadcast();
}
void URXPlayerStatComponent::StartShieldRegen()
{
    if (bIsShieldRegenActive) return;

    bIsShieldRegenActive = true;

	// 레벨이동에 객체 UI,델리게이트 소멸 재생성 문제 해결을 위한 약한 참조 람다 활용
	TWeakObjectPtr<URXPlayerStatComponent> WeakThis(this);
    GetWorld()->GetTimerManager().SetTimer(ShieldRegenTimer, [WeakThis]()
        {
			if (WeakThis.IsValid())
			{
				WeakThis->ShieldRegenAction();
			}
        }, 8.00f, false);
}
void URXPlayerStatComponent::ShieldRegenAction()
{
	SetShieldToGI(MaxShield); 
	bIsShieldRegenActive = false;
}
