// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPuzzelEventManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class RETURN_XENIA_API URXPuzzelEventManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URXPuzzelEventManageComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartPuzzelMode();
	virtual void StartPuzzelMode_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndPuzzelMode();
	virtual void EndPuzzelMode_Implementation();

	UPROPERTY()
	TObjectPtr<class ARXPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PuzzelCamera")
	TObjectPtr<ACameraActor> PuzzelModeCamera;

private:
	void SwitchToCamera(AActor* NewCamera, float BlendTime) const;
};
