// Copyright Epic Games, Inc. All Rights Reserved.

#include "RETURN_XENIAGameMode.h"
#include "RETURN_XENIACharacter.h"
#include "UObject/ConstructorHelpers.h"

ARETURN_XENIAGameMode::ARETURN_XENIAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
