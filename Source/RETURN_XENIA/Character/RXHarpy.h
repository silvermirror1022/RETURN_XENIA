// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "RXHarpy.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXHarpy : public ARXCharacterBase
{
	GENERATED_BODY()
public:
	ARXHarpy();

protected:
	void BeginPlay() override;
};
