// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXKnotHanger.generated.h"

class UCameraComponent;

UCLASS()
class RETURN_XENIA_API ARXKnotHanger : public AActor
{
	GENERATED_BODY()
	
public:	
	ARXKnotHanger();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeToCamView();
	virtual void ChangeToCamView_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReturnToPlayerView();
	virtual void ReturnToPlayerView_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HangKnotAction();
	virtual void HangKnotAction_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSetting")
	TObjectPtr<ACameraActor> KnotShowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 isCamView : 1;

	// 1층 듀토리얼 퍼즐 매듭 획득 체크 함수
	UFUNCTION(BlueprintCallable)
	bool IsAcquiredKnot_Tutorial();

	// 2층 듀토리얼 퍼즐 매듭 획득 체크 함수
	UFUNCTION(BlueprintCallable)
	bool IsAcquiredKnot_1F();

	// 3층 듀토리얼 퍼즐 매듭 획득 체크 함수
	UFUNCTION(BlueprintCallable)
	bool IsAcquiredKnot_2F();

	// 넘길 타입 변수들 Tutorial, 1F, 2F
	UFUNCTION(BlueprintCallable)
	void UseKnotItem(FString KnotHangerType);
	UPROPERTY()
	TObjectPtr<class ARXPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

	void SwitchToCamera(AActor* NewCamera, float BlendTime) const;
};
