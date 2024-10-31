// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RXHarpyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXHarpyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
    URXHarpyAnimInstance();

protected:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter>Owner;

    // Animation Variable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	uint8 bIsMove : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	uint8 bIsDetected : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	uint8 bIsAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	uint8 bIsIdle : 1;
};
