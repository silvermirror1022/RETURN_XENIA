// Fill out your copyright notice in the Description page of Project Settings.
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "System/RXAssetManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RXPlayer.h"
#include "Data/RXDialogueData.h"
#include "Character/RXNonPlayer.h"

ARXNonPlayer::ARXNonPlayer()
{
    DialogueWidgetInstance = nullptr;
    DialogueData = nullptr;
    DialogueIndex = 0;
    bIsTalking = false;
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
    bIsTalking = true;


    // 플레이어를 바라보게 하기
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  // 첫 번째 플레이어를 가져옴
    if (PlayerCharacter)
    {
        // ARXPlayer로 캐스팅
        ARXPlayer* RXPlayer = Cast<ARXPlayer>(PlayerCharacter);
        if (RXPlayer)
        {
            // 플레이어와 NPC의 위치 계산
            FVector PlayerLocation = RXPlayer->GetActorLocation();
            FVector NPCLocation = GetActorLocation();

            // NPC가 플레이어를 바라보도록 회전값을 계산
            FRotator LookAtRotation = (PlayerLocation - NPCLocation).Rotation();

            // NPC의 회전값을 적용 (y축만 회전)
            SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));  // Pitch와 Roll은 고정, Yaw만 변경


            // 대화 시작 시 이동 비활성화
            if (RXPlayer->Controller)
            {
                // 이동 입력 무시 (PlayerController를 통해)
                RXPlayer->Controller->SetIgnoreMoveInput(true);
            }
        }

    }
    
    // 위젯 인스턴스 생성
    if (WidgetClass)
    {
        DialogueWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (DialogueWidgetInstance)
        {
            // 위젯을 뷰포트에 추가
            DialogueWidgetInstance->AddToViewport();

            // Text 위젯을 찾고, 대화 텍스트를 업데이트, NPC 이름 업데이트
            DialogueTextBlock = Cast<UTextBlock>(DialogueWidgetInstance->GetWidgetFromName("DialogueText"));
            NPCNameTextBlock = Cast<UTextBlock>(DialogueWidgetInstance->GetWidgetFromName("NPCName"));
            if (DialogueTextBlock && NPCNameTextBlock)
            {
                NPCNameTextBlock->SetText(NPCName);
                DisplayDialogue();
            }
        }
    }
}

void ARXNonPlayer::DisplayDialogue()
{
    if (DialogueData && DialogueTextBlock)
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
    bIsTalking = false;

    // 대화 종료 시 위젯을 제거
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->RemoveFromViewport();
        DialogueWidgetInstance = nullptr;
        DialogueTextBlock = nullptr;
    }
    // 플레이어 이동 중지 해제
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  
    if (PlayerCharacter)
    {
        ARXPlayer* RXPlayer = Cast<ARXPlayer>(PlayerCharacter);
        if (RXPlayer)
        {
            RXPlayer->Controller->SetIgnoreMoveInput(false);  // 이동 입력 허용
        }
    }
}


