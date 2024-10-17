// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "Interface/RXPlayerHUDInterface.h"
#include "RXPlayer.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXPlayer : public ARXCharacterBase, public IRXPlayerHUDInterface
{
	GENERATED_BODY()
	
public:
	ARXPlayer();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

	
protected: // Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;


protected: // InputMovement Logic Section
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


protected: // DamagedByPawn(Harpy) Section
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


protected: // Dead Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;


protected: // Stat Section -> Player Hp,Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URXPlayerStatComponent> Stat;


protected: 	//PlayerHUD Interface Virtual Func override Implementation
	virtual void SetupHUDWidget(class URXHUDWidget* InHUDWidget) override;

};
