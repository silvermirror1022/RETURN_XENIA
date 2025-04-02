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

	UPROPERTY()
	float MouseSensitivityValue; // 마우스 민감도

	FSliderValues()
		: BrightnessValue(1.0f), MasterVolumeValue(1.0f), MusicVolumeValue(1.0f), SFXVolumeValue(1.0f), MouseSensitivityValue(1.0f) {}
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

	// 체크포인트 정보 (Transform으로 위치와 회전 한번에 관리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckPoint")
	FTransform CheckpointTransform;
	// 레벨 전환시 저장해 놓을 태그타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DestinationTag")
	FGameplayTag CurrentDestinationTag; 
	// 필요한 경우 블루프린트에서 목적지 설정
	UFUNCTION(BlueprintCallable, Category = "Teleport")
	void SetDestinationTag(FGameplayTag NewDestinationTag) { CurrentDestinationTag = NewDestinationTag; }
	// 플레이어가 있던 곳의 레벨이름
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CheckPoint")
	FName CurrentLevelName;
	// 플레이어가 컨티뉴를 했는지
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CheckPoint")
	bool bIsContinueGame;;

public:
	// 메모리 획득 여부를 저장하는 배열 (총5개)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryStatus")
	TArray<FStatus> MemoryStatusArray; 
	// 프로필 장비 획득 여부를 저장하는 배열 (망토, 동생)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProfileStatus")
	TArray<FStatus> ProfileStatusArray; 
	// 아이템 획득 여부를 저장하는 배열 (매듭문자 7개, 파피루스3개, 힌트종이 => 11개)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemStatus")
	TArray<FStatus> ItemStatusArray; 
	// 퍼즐 클리어 유무 배열 (서브맵1,2,3,4,5,템플 => 6개)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzelClearStatus")
	TArray<FStatus> PuzzelClearStatusArray;
	// 듀토리얼 알림 유무 배열 (6개)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TutorialNotifyStatus")
	TArray<FStatus> TutorialNotifyStatusArray;
	// 맵 탐험 클리어 체크 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservedMapStatus")
	int32 ObservedMapStatus; 

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

	// 보스전 실패시 노아 프로필 초기화 함수
	UFUNCTION(BlueprintCallable, Category = "ProfileStatus")
	void SetBossStageProfileStatusInit();
public:
	// 아이템 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "ItemStatus")
	bool SetItemStatusAcquired(FString StatusName);

	UFUNCTION(BlueprintCallable, Category = "ItemStatus")
	bool IsItemStatusAcquired(FString StatusName) const;

	// 퍼즐 클리어 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "PuzzelStatus")
	bool SetPuzzelStatusAcquired(FString StatusName);

	UFUNCTION(BlueprintCallable, Category = "PuzzelStatus")
	bool IsPuzzelStatusAcquired(FString StatusName) const;

	// 듀토리얼 알림 유무 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "TutorialNotifyStatus")
	bool SetTutorialNotifyStatusAcquired(FString StatusName);

	UFUNCTION(BlueprintCallable, Category = "TutorialNotifyStatus")
	bool IsTutorialNotifyStatusAcquired(FString StatusName) const;



	// 맵 탐험 클리어 상태 설정 및 상태 확인 함수 섹션
	UFUNCTION(BlueprintCallable, Category = "ObservedMapStatus")
	void SetObservedMapStatus(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "ObservedMapStatus")
	int ReturnObservedMapStatus();
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
	
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	float GetMouseSensitivityValue() const { return SliderValues.MouseSensitivityValue; }

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void SetMouseSensitivityValue(float Value) { SliderValues.MouseSensitivityValue = Value; }

	// 게임 세팅 언어 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language Settings")
	bool bIsKorean;

	UFUNCTION(BlueprintCallable)
	void InitializeAllVariable();

	// 재앙이 발생한 후 스폰할 NPC들 대화 세부 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	bool bIsAfterDisaster;
	// 여동생 대화 이벤트 종료 확인 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	bool bIsKairaDialogueEventFinished;
	// 안투크 대화 이벤트 종료 확인 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	bool bIsAntuqDialogueEventFinished;
	// 아마르카 대화 이벤트 종료 확인 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	bool bIsAmarkaDialogueEventFinished; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	// 아마르카 아이템 이벤트 종료 확인
	bool bIsAmarkaDialogueItemEventFinished;
	// 위닉 대화 이벤트 종료 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
	bool bIsWinikDialogueEventFinished;  
	// 플레이어가 얻은 파피루스 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sub Settings")
	int32 AcquiredPapyrusNum; 
	// 플레이어가 받은 보스 힌트 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sub Settings")
	int32 AcquiredBossHintNum; 
	// 노아 눈꺼풀 이벤트 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sub Settings")
	bool bIsNoahGetup; 

};
