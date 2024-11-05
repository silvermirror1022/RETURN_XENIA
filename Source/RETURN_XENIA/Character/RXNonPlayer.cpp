// Fill out your copyright notice in the Description page of Project Settings.
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "System/RXAssetManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Data/RXDialogueData.h"
#include "Character/RXNonPlayer.h"

ARXNonPlayer::ARXNonPlayer()
{
    DialogueData = nullptr;
    DialogueIndex = 0;
}

void ARXNonPlayer::BeginPlay()
{
    Super::BeginPlay();

    /*
    
    NPCType이 DialogueData_NPC_Papamama와 매칭되는지 확인 test code => 확인

    if (NPCType.MatchesTag(RXGameplayTags::DialogueData_NPC_Papamama))
    {
        D(FString::Printf(TEXT("Type completed : %s"), *NPCType.ToString()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NPCType does not match DialogueData_NPC_Papamama."));
    }
    
    */

    // DialogueData를 성공적으로 가져왔는지 확인
    if (DialogueData = URXAssetManager::GetAssetByName<URXDialogueData>("DialogueData"))
    {
        check(DialogueData);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot Load DialogueData."));
    }
        
}

void ARXNonPlayer::StartDialogue()
{
    DialogueIndex = 0;

    // 위젯 인스턴스 생성
    if (WidgetClass)
    {
        UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (WidgetInstance)
        {
            // 위젯을 뷰포트에 추가
            WidgetInstance->AddToViewport();

            // Text 위젯을 찾고, 대화 텍스트를 업데이트
            UTextBlock* DialogueTextBlock = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName("DialogueText"));
            if (DialogueTextBlock)
            {
                DisplayDialogue(DialogueTextBlock);
            }
        }
    }
}

void ARXNonPlayer::DisplayDialogue(UTextBlock* DialogueTextBlock)
{
    if (DialogueData)
    {
        const FRXDiaglogueData* DialogueEntry = DialogueData->FindDialogueCharTypeByTag(NPCType);
        if (DialogueEntry && DialogueIndex < DialogueEntry->DialogueText.Num())
        {
            // 대화 텍스트를 업데이트
            DialogueTextBlock->SetText(FText::FromName(DialogueEntry->DialogueText[DialogueIndex]));
            UE_LOG(LogTemp, Log, TEXT("Current Dialogue: %s"), *DialogueEntry->DialogueText[DialogueIndex].ToString());
            DialogueIndex++;
        }
        else
        {
            EndDialogue();
        }
    }
}

void ARXNonPlayer::EndDialogue()
{
    UE_LOG(LogTemp, Log, TEXT("Dialogue has ended."));
    DialogueIndex = 0;
}


