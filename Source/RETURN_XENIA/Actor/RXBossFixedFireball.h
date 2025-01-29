// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXBossFixedFireball.generated.h"

UCLASS()
class RETURN_XENIA_API ARXBossFixedFireball : public AActor
{
	GENERATED_BODY()
	
public:	

	ARXBossFixedFireball();

protected:

	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
	float Speed;

	void LaunchProjectile(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void ResetFireball();

private:
	UPROPERTY(EditAnywhere, Category = "ProjectileMovement")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	FTimerHandle DeactivationTimer;

	FVector InitialLocation;
};
