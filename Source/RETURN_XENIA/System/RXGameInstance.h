// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "RXGameInstance.generated.h"

/**
 * 
 */
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryStatus")
	TArray<bool> MemoryStatusArray; //메모리 획득 여부 설정 변수 (총 4개)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProfileStatus")
	TArray<bool> ProfileStatusArray; //프로필 장비 획득 유무 변수 (망토 and 동생)
};
