// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameplayTagContainer.h"
#include "RXGameInstance.h"
#include "RXSaveGame.generated.h"

/*
 * URXGameInstance의 모든 변수 상태를 저장하는 SaveGame 클래스.
 * 블루프린트에서 상속받아 확장
 */

UCLASS()
class RETURN_XENIA_API URXSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	URXSaveGame();

	/** 체크포인트 정보 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FTransform CheckpointTransform;

	/** 체크포인트 정보 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FName CurrentLevelName;

	/** 현재 목적지 태그 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FGameplayTag CurrentDestinationTag;

	/** 메모리 상태 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FStatus> MemoryStatusArray;

	/** 프로필 상태 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FStatus> ProfileStatusArray;

	/** 아이템 상태 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FStatus> ItemStatusArray;

	/** 퍼즐 클리어 상태 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FStatus> PuzzelClearStatusArray;

	/** 플레이어 체력 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 GI_Hp;

	/** 플레이어 방패 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 GI_Shield;

	/** 게임 설정 슬라이더 값들 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FSliderValues SliderValues;

	/** 언어 설정 (Korean 여부) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsKorean;

	/** 재앙 이후 관련 설정 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsAfterDisaster;

	/** 대화 이벤트 상태들 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsKairaDialogueEventFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsAntuqDialogueEventFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsAmarkaDialogueEventFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsAmarkaDialogueItemEventFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsWinikDialogueEventFinished;

	/** 기타 변수들 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 ObservedMapStatus; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 AcquiredPapyrusNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 AcquiredBossHintNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool bIsNoahGetup;

public:

	 // 게임 인스턴스의 현재 데이터를 이 SaveGame 객체로 복사
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void CaptureDataFromGameInstance(URXGameInstance* GameInstance);


	//이 SaveGame 객체에 저장된 데이터를 게임 인스턴스에 적용
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void ApplyDataToGameInstance(URXGameInstance* GameInstance);
};
