// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RXPlayerInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URXPlayerInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *   
 */
class RETURN_XENIA_API IRXPlayerInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact_IA_EKey() = 0;
	virtual void Interact_IA_TabKey() = 0;

};
