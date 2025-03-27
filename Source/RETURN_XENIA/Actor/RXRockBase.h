// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXRockBase.generated.h"

UCLASS()
class RETURN_XENIA_API ARXRockBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ARXRockBase();

protected:

	virtual void BeginPlay() override;

	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

public:
	UPROPERTY(EditAnywhere, Category = "RockSetting")
	TObjectPtr<AActor> ImpulseDirActor;

	UPROPERTY(EditAnywhere, Category = "RockSetting")
	float ImpulseForce;

	UPROPERTY(EditAnywhere, Category = "RockSetting")
	bool bIsSmallRock;

	// static Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	// Arrow Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UArrowComponent> ArrowComponent;

private:
	UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }

};
