// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RXPlayerStatComponent.h"


URXPlayerStatComponent::URXPlayerStatComponent()
{
	//플레이어 Hp 설정 임시코드
	MaxHp = 200.0f;
	CurrentHp = MaxHp;

	bWantsInitializeComponent = true; //InitializeComponent 함수 호출을 위해
}


void URXPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetHp(MaxHp);
}

void URXPlayerStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);
	OnPlayerHpChanged.Broadcast(CurrentHp); //플레이어 데미지로 인해 체력 변화시 델리게이트 호출
}


float URXPlayerStatComponent::ApplyDamage(float InDamage)
{
	//플레이어가 데미지를 입었을 때 함수 섹션

	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);
	//FMath::Clamp(a,b,c) => a를 b와 c사이로 설정
	SetHp(PrevHp - ActualDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		//Dead
		OnPlayerHpZero.Broadcast(); //만약 플레이어 체력 0이 되면 델리게이트 호출
	}
	return ActualDamage;
}
