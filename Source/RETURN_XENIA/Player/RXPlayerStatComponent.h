﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPlayerStatComponent.generated.h"


// 플레이어가 Hp가 0이 될 때 호출 델리게이트 
DECLARE_MULTICAST_DELEGATE(FOnPlayerHpZeroDelegate); 
// 플레이어가 Hp가 변화 감지 호출 델리게이트
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerHpAndShieldChangedDelegate, int32 /*CurrentHp*/,int32 /*CurrentShield*/);
// 플레이어 쉴드 변화 감지 호출 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerShieldRegenSecChangedDelegate, int32 /*CurrentIndex*/);
// 플레이어가 쉴드가 풀차지 될 때 호출 델리게이트 
DECLARE_MULTICAST_DELEGATE(FOnPlayerShieldFullDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RETURN_XENIA_API URXPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URXPlayerStatComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 위에 선언했던 델리게이트 변수로 등록
	FOnPlayerHpZeroDelegate OnPlayerHpZero;
	FOnPlayerHpAndShieldChangedDelegate OnPlayerHpAndShieldChanged;
	FOnPlayerShieldRegenSecChangedDelegate OnPlayerShieldSecRegenChanged;
	FOnPlayerShieldFullDelegate OnPlayerShieldFull;

protected:
	// 게임인스턴스에 해당 변수를 기록하는 함수
	UPROPERTY()
	TObjectPtr<class URXGameInstance> GI;

	void SetHpToGI(int32 NewHp);
	void SetShieldToGI(int32 NewShield);
	URXGameInstance* GetGameInstance();

public:
	// 체력과 쉴드 시스템 게터 & 세터
	FORCEINLINE int32 GetMaxHp() const { return MaxHp; }
	FORCEINLINE int32 GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE int32 GetMaxShield() const { return MaxShield; }
	FORCEINLINE int32 GetCurrentShield() const { return CurrentShield; }

	void InitializeStatComponent();

	// 데미지 적용 함수 & 회복 함수
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(int32 InDamage);
	UFUNCTION(BlueprintCallable)
	void ApplyHealing(int32 InHealAmount);

protected:
	// 쉴드, 체력 섹션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 MaxHp;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 MaxShield;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 CurrentShield;
	
public:
	// 쉴드 보유 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
	uint8 bHasShield : 1; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat")
	uint8 bIsImmortal : 1; // 플레이어 피격시 무적변수

	// 캐릭터 피격/정상 머터리얼 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
	TObjectPtr<UMaterialInterface> RedMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
	TObjectPtr<UMaterialInterface> DefaultMaterial;

	// 피격 시 재생할 2D 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> HitSound;

private:
	FTimerHandle ShieldRegenTimer; // 쉴드 회복 타이머
	void StartShieldRegen();
	uint8 bIsShieldRegenActive : 1;
	void ShieldRegenAction();

	float ImmortalTime = 1.0f; // 무적 시간 및 타이머
	FTimerHandle ImmortalTimer;
	void ResetImmortalState();

	/*int32 FlashToggleCount;  // 피격 머터리얼변화 관련 변수
	FTimerHandle MaterialFlashTimer;
	void StartMaterialFlash(); // 피격 머터리얼변화 관련 함수
	void ToggleMaterialFlash();*/

};