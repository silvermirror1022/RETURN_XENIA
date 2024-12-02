// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "RXGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FString Name; // 상태 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool bIsAcquired; // 획득 여부
};

USTRUCT(BlueprintType)
struct FSliderValues
{
	GENERATED_BODY()

public:

	UPROPERTY()
	float BrightnessValue; // 게임밝기

	UPROPERTY()
	float MasterVolumeValue; // 게임 마스터볼륨

	UPROPERTY()
	float MusicVolumeValue; // 게임 배경 볼륨

	UPROPERTY()
	float SFXVolumeValue; // 게임 효과음 볼륨

	FSliderValues()
		: BrightnessValue(1.0f), MasterVolumeValue(1.0f), MusicVolumeValue(1.0f), SFXVolumeValue(1.0f) {}
};

UCLASS()
class RETURN_XENIA_API URXGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URXGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DestinationTag")
	FGameplayTag CurrentDestinationTag; //레벨 전환시 저장해 놓을 태그타입

	UFUNCTION(BlueprintCallable, Category = "Teleport") //필요한 경우 블루프린트에서 목적지 설정
	void SetDestinationTag(FGameplayTag NewDestinationTag) { CurrentDestinationTag = NewDestinationTag; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryStatus")
	TArray<FStatus> MemoryStatusArray; // 메모리 획득 여부를 저장하는 배열 (총4개)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProfileStatus")
	TArray<FStatus> ProfileStatusArray; // 프로필 장비 획득 여부를 저장하는 배열 (망토, 동생)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemStatus")
	TArray<FStatus> ItemStatusArray; // 아이템 획득 여부를 저장하는 배열 (매듭문자 6개, 심장, 힌트종이)

public:
	// 메모리 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "MemoryStatus")
	bool SetMemoryStatusAcquired(FString StatusName);
	UFUNCTION(BlueprintCallable, Category = "MemoryStatus")
	bool IsMemoryStatusAcquired(FString StatusName) const;

public:
	// 프로필 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "ProfileStatus")
	bool SetProfileStatusAcquired(FString StatusName);

	UFUNCTION(BlueprintCallable, Category = "ProfileStatus")
	bool IsProfileStatusAcquired(FString StatusName) const;

public:
	// 아이템 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "ITemStatus")
	bool SetItemStatusAcquired(FString StatusName);

	UFUNCTION(BlueprintCallable, Category = "ITemStatus")
	bool IsItemStatusAcquired(FString StatusName) const;

public:
	// 플레이어 체력, 방패 섹션
	UPROPERTY()
	int32 GI_Hp;

	UPROPERTY()
	int32 GI_Shield;

	// 체력 쉴드 게터, 세터
	FORCEINLINE int32 GetGI_Hp() const { return GI_Hp; }
	FORCEINLINE void SetGI_Hp(int32 InGI_Hp) { GI_Hp = InGI_Hp; }

	FORCEINLINE int32 GetGI_Shield() const { return GI_Shield; }
	FORCEINLINE void SetGI_Shield(int32 InGI_Shield) { GI_Shield = InGI_Shield; }

	// 게임 셋팅 볼륨, 밝기 저장 변수
	UPROPERTY()
	FSliderValues SliderValues;

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	float GetBrightnessValue() const { return SliderValues.BrightnessValue; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void SetBrightnessValue(float Value) { SliderValues.BrightnessValue = Value; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	float GetMasterVolumeValue() const { return SliderValues.MasterVolumeValue; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void SetMasterVolumeValue(float Value) { SliderValues.MasterVolumeValue = Value; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	float GetMusicVolumeValue() const { return SliderValues.MusicVolumeValue; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void SetMusicVolumeValue(float Value) { SliderValues.MusicVolumeValue = Value; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	float GetSFXVolumeValue() const { return SliderValues.SFXVolumeValue; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void SetSFXVolumeValue(float Value) { SliderValues.SFXVolumeValue = Value; }

};
