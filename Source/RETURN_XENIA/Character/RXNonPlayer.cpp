﻿// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/RXNonPlayer.h"
#include "System/RXAssetManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RXPlayer.h"
#include "Data/RXDialogueData.h"
#include "System/RXGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/RXPlayerController.h"
#include "RXDebugHelper.h"
ARXNonPlayer::ARXNonPlayer()
{
    PrimaryActorTick.bCanEverTick = false;
    DialogueWidgetInstance = nullptr;
    Kor_DialogueData = nullptr;
    Eng_DialogueData = nullptr;
    DialogueIndex = 0;
    bIsTalking = false;
}

void ARXNonPlayer::BeginPlay()
{
    Super::BeginPlay();

    GI = Cast<URXGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (Eng_DialogueData = URXAssetManager::GetAssetByName<URXDialogueData>("Eng_DialogueData"))
    {
        check(Eng_DialogueData);
    }
    if (Kor_DialogueData = URXAssetManager::GetAssetByName<URXDialogueData>("Kor_DialogueData"))
    {
        check(Kor_DialogueData);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot Load DialogueData."));
    }
	
}

void ARXNonPlayer::StartDialogue()
{
    if (bIsTalking) // 중복 방지
    {
        UE_LOG(LogTemp, Warning, TEXT("Dialogue is already in progress."));
        return;
    }

    DialogueIndex = 0;
    bIsTalking = true;

    if (ARXPlayerController* PlayerController = Cast<ARXPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PlayerController->SetDialogueState(true); // 대화 시작
    }

    // 플레이어를 바라보게 하기
	// 첫 번째 플레이어를 가져옴
    if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        // ARXPlayer로 캐스팅
        if (ARXPlayer* RXPlayer = Cast<ARXPlayer>(PlayerCharacter))
        {
            // 플레이어와 NPC의 위치 계산
            FVector PlayerLocation = RXPlayer->GetActorLocation();
            FVector NPCLocation = GetActorLocation();

            // NPC가 플레이어를 바라보도록 회전값을 계산
            FRotator LookAtRotation = (PlayerLocation - NPCLocation).Rotation();

            // NPC의 회전값을 적용 (y축만 회전)
            SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));  // Pitch와 Roll은 고정, Yaw만 변경


            // 점프 중이라면 강제 착지 처리
            if (RXPlayer->GetCharacterMovement()->IsFalling())
            {
                GetCharacterMovement()->StopMovementImmediately();  // 즉시 착지
                RXPlayer->Landed(FHitResult()); // 강제 착지 이벤트 호출
                RXPlayer->GetCharacterMovement()->SetMovementMode(MOVE_Walking); // 걷기 모드 복귀
            }

            // 이동 및 점프 차단
            if (RXPlayer->Controller)
            {
                RXPlayer->Controller->SetIgnoreMoveInput(true);
                RXPlayer->GetCharacterMovement()->SetMovementMode(MOVE_None);
            }
        }

    }

    // NPC에 해당 캐싱된 대화 시작 애님몽타주 플레이
    PlayDialogueMontage();


    // 기존 위젯 제거
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->RemoveFromParent();
        DialogueWidgetInstance = nullptr;
    }

    if (GI)
    {
        TSubclassOf<UUserWidget> SelectedWidgetClass = GI->bIsKorean ? KorWidgetClass : EngWidgetClass;
        if (SelectedWidgetClass)
        {
            DialogueWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), SelectedWidgetClass);
            if (DialogueWidgetInstance)
            {
                DialogueWidgetInstance->AddToViewport();
                DialogueTextBlock = Cast<UTextBlock>(DialogueWidgetInstance->GetWidgetFromName("DialogueText"));
                NPCNameTextBlock = Cast<UTextBlock>(DialogueWidgetInstance->GetWidgetFromName("NPCName"));

                if (DialogueTextBlock && NPCNameTextBlock)
                {   // 한국어 영어 설정에 따른 이름 변경
                    if (GI->bIsKorean)
                    {
                        NPCNameTextBlock->SetText(NPCKor_Name);
                    }
                    else
                    {
                        NPCNameTextBlock->SetText(NPCEng_Name);
                    }

                    DisplayDialogue();
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create dialogue widget."));
            }
        }
    }

}

void ARXNonPlayer::DisplayDialogue()
{
   
    if (!GI || !DialogueTextBlock) return;
    //D(FString::Printf(TEXT("bIsTalking: %d, DialIndex: %d"), bIsTalking, DialogueIndex));

    // 한국어/영어에 따라 적절한 DialogueData 선택
    const URXDialogueData* SelectedDialogueData = GI->bIsKorean ? Kor_DialogueData : Eng_DialogueData;
    if (!SelectedDialogueData) return;

    // NPCType으로 대화 데이터를 검색
    const FRXDiaglogueData* DialogueEntry = SelectedDialogueData->FindDialogueCharTypeByTag(NPCType);
    if (DialogueEntry && DialogueIndex < DialogueEntry->DialogueText.Num())
    {
        // 대화 텍스트 업데이트
        DialogueTextBlock->SetText(FText::FromName(DialogueEntry->DialogueText[DialogueIndex]));
        //UE_LOG(LogTemp, Log, TEXT("Current Dialogue: %s"), *DialogueEntry->DialogueText[DialogueIndex].ToString());

        // 사운드 출력 (NPCType에 맞는 하나의 사운드만 재생)
        if (DialogueEntry->DialogueSound)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), DialogueEntry->DialogueSound);
        }
        DialogueIndex++;
    }
    else
    {
        EndDialogue();
    }
}

void ARXNonPlayer::EndDialogue()
{
    UE_LOG(LogTemp, Log, TEXT("Dialogue has ended."));

    // 대화 종료 시 위젯을 제거
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->RemoveFromParent();
        DialogueWidgetInstance = nullptr;
        DialogueTextBlock = nullptr;
    }

    DialogueIndex = 0;
    bIsTalking = false;

    // 플레이어 이동 중지 해제
    if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        if (ARXPlayer* RXPlayer = Cast<ARXPlayer>(PlayerCharacter))
        {
            RXPlayer->Controller->SetIgnoreMoveInput(false);  // 이동 입력 허용
            RXPlayer->GetCharacterMovement()->SetMovementMode(MOVE_Walking); // 이동 + 점프 가능

            // 즉시 ResetDetectedActors() 호출하는 대신, 0.1초 후 실행
            GetWorld()->GetTimerManager().SetTimerForNextTick([RXPlayer]() {
                RXPlayer->ResetDetectedActors();
                });
        }
    }
    // 예외처리 변수 해제
    if (ARXPlayerController* PlayerController = Cast<ARXPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PlayerController->SetDialogueState(false); 
    }

    DialoguePopupEvent(); // 블루프린트에서 커스텀화한 함수가 있다면 대화종료후 호출
}

void ARXNonPlayer::PlayDialogueMontage() const
{
    // 애니메이션 몽타주 재생 (동시에 대화 시작)
    if (DialogueMontage && GetMesh() && GetMesh()->GetAnimInstance())
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        AnimInstance->Montage_Play(DialogueMontage);
    }
}

void ARXNonPlayer::DialoguePopupEvent_Implementation()
{
    // 대화종료후 처리해야할 커스텀 이벤트들 블루프린트에서 처리
    // 이벤트 관련은 게임인스턴스 bool변수 true로 아마르카, 안투크, 위닉
}


