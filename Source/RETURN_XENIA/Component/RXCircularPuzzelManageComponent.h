// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXCircularPuzzelManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETURN_XENIA_API URXCircularPuzzelManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	URXCircularPuzzelManageComponent();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzel")
	int32 TargetScore;

	UPROPERTY()
	TArray<int32> OuterWheel;
	UPROPERTY()
	TArray<int32> MiddleWheel;
	UPROPERTY()
	TArray<int32> InnerWheel;

	int32 CurrentSelectedWheel;

	int32 OuterIndex;
	int32 MiddleIndex;
	int32 InnerIndex;

	//점수 계산 및 확인 함수
	int32 CalculateScore() const;
	bool IsCorrectAnswer() const;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzelCamera")
	AActor* PuzzelModeCamera;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartCircularPuzzelMode();
	virtual void StartCircularPuzzelMode_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndCircularPuzzelMode();
	virtual void EndCircularPuzzelMode_Implementation();

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
	void ExitCircularPuzzel();
	virtual void ExitCircularPuzzel_Implementation();

private:
	void RotateWheel(int32& CurrentIndex, const TArray<int32>& Wheel, bool bClockwise);

	UPROPERTY()
	TObjectPtr<class ARXPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

	void SwitchToCamera(AActor* NewCamera, float BlendTime) const;
};
