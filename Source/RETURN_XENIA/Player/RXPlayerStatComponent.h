// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPlayerStatComponent.generated.h"

//플레이어가 Hp가 0이 될 때 호출 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnPlayerHpZeroDelegate); 

//플레이어가 Hp가 변화 감지 호출 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerHpChangedDelegate, float /*CurrentHp*/);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RETURN_XENIA_API URXPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URXPlayerStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	//위에 선언했던 델리게이트 변수로 등록
	FOnPlayerHpZeroDelegate OnPlayerHpZero;
	FOnPlayerHpChangedDelegate OnPlayerHpChanged;

protected:
	void SetHp(float NewHp);

public:
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }

	float ApplyDamage(float InDamage);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHp;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentHp;

};