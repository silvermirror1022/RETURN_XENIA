// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "RXPlayer.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXPlayer : public ARXCharacterBase
{
	GENERATED_BODY()
	
public:
	ARXPlayer();

protected:
	// Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

};
