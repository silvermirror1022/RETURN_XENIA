// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPlayerStatComponent.generated.h"

class URXGameInstance;

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
	TObjectPtr<URXGameInstance> GI;

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
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	uint8 bHasShield : 1; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	uint8 bIsImmortal : 1; // 플레이어 피격시 무적변수

private:
	FTimerHandle ShieldRegenTimer; // 쉴드 회복 타이머
	void StartShieldRegen();
	uint8 bIsShieldRegenActive : 1;
	void ShieldRegenAction();

	float ImmortalTime = 0.5f; // 무적 시간 및 타이머
	FTimerHandle ImmortalTimer;
	void ResetImmortalState();
};