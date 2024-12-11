// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXPuzzelBase.generated.h"

UCLASS()
class RETURN_XENIA_API ARXPuzzelBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARXPuzzelBase();

protected:
	virtual void BeginPlay() override;

public:	
	void PuzzelEventStart();

};
