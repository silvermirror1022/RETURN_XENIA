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
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ShowKnotWithCam();
	virtual void ShowKnotWithCam_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraView")
	TObjectPtr<ACameraActor> PuzzelModeCamera;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	//TObjectPtr<UCameraComponent> HangerCamera;
};
