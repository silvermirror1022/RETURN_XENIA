// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RXDialogueData.h"

const FRXDiaglogueData* URXDialogueData::FindDialogueCharTypeByTag(const FGameplayTag& InputTag) const
{
    for (const FRXDiaglogueData& DialogueDataEntry : DialogueData)
    {
        if (DialogueDataEntry.DialogueCharTypeTag == InputTag)
        {
            return &DialogueDataEntry;  
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Can't find DialogueData for InputTag [%s]"), *InputTag.ToString());

    return nullptr;  
}