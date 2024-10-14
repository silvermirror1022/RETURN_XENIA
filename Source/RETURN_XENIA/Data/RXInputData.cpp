// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RXInputData.h"

const UInputAction* URXInputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FRXInputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s]"), *InputTag.ToString());

	return nullptr;
}
