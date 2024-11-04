// Fill out your copyright notice in the Description page of Project Settings.
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "System/RXAssetManager.h"
#include "Character/RXNonPlayer.h"

ARXNonPlayer::ARXNonPlayer()
{
    
}

void ARXNonPlayer::BeginPlay()
{
    Super::BeginPlay();

    //NPCType이 DialogueData_NPC_Papamama와 매칭되는지 확인
    if (NPCType.MatchesTag(RXGameplayTags::DialogueData_NPC_Papamama))
    {
        D(FString::Printf(TEXT("Type completed : %s"), *NPCType.ToString()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NPCType does not match DialogueData_NPC_Papamama."));
    }
}

void ARXNonPlayer::StartDialogue()
{
    
}

void ARXNonPlayer::DisplayDialogue()
{
}

void ARXNonPlayer::EndDialogue()
{
}
