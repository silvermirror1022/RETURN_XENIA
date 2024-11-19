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
	TArray<FStatus> ItemStatusArray; // 아이템 획득 여부를 저장하는 배열 (매듭문자 5개, 심장, 힌트종이)

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
};
