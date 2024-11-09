// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_Rule.h"
#include "RX_SubmapPuzzle_Die.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARX_SubmapPuzzle_Die : public ARX_SubmapPuzzle_Rule
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
