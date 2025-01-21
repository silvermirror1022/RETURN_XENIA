// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/RXPuzzelBase.h"
#include "RXCircularPuzzelBase.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXCircularPuzzelBase : public ARXPuzzelBase
{
	GENERATED_BODY()

public:
	ARXCircularPuzzelBase();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzel")
	int32 TargetScore;

	UPROPERTY()
	TArray<int32> OuterWheel;
	UPROPERTY()
	TArray<int32> MiddleWheel;
	UPROPERTY()
	TArray<int32> InnerWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzel")
	int32 CurrentSelectedWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzel")
	int32 OuterIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzel")
	int32 MiddleIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzel")
	int32 InnerIndex;

	// 회전중인지 체크 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 isRotating : 1;

	// 점수 계산 및 확인 함수
	int32 CalculateScore() const;
	UFUNCTION(BlueprintCallable)
	bool IsCorrectAnswer() const;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzelCamera")

	TObjectPtr<ACameraActor> PuzzelModeCamera;

	// 부모의 PuzzelEventStart, PuzzelEventFinish를 오버라이드
	virtual void PuzzelEventStart_Implementation() override;
	virtual void PuzzelEventFinish_Implementation() override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RotateToClockWise();
	virtual void RotateToClockWise_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RotateToCounterClockWise();
	virtual void RotateToCounterClockWise_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SwitchSelectedWheel();
	virtual void SwitchSelectedWheel_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MovePlayerLocation();
	virtual void MovePlayerLocation_Implementation();

private:
	void RotateWheel(int32& CurrentIndex, const TArray<int32>& Wheel, bool bClockwise);

	UPROPERTY()
	TObjectPtr<class ARXPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

	void SwitchToCamera(AActor* NewCamera, float BlendTime) const;
};
