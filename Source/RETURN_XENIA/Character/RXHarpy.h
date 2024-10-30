// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RXHarpy.generated.h"

UCLASS()
class RETURN_XENIA_API ARXHarpy : public ACharacter
{
	GENERATED_BODY()

public:
	ARXHarpy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
