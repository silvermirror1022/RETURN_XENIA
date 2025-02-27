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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSetting")
	TObjectPtr<ACameraActor> KnowShowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 isCamView : 1;

	UPROPERTY()
	TObjectPtr<class ARXPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

	void SwitchToCamera(AActor* NewCamera, float BlendTime) const;
};
