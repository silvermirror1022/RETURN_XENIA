// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPuzzelStartComponent.generated.h"


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class RETURN_XENIA_API URXPuzzelStartComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URXPuzzelStartComponent();

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
};