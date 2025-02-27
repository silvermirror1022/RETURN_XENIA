// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXKnotHanger.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RXPlayer.h"
#include "Player/RXPlayerController.h"
#include "Camera/CameraActor.h"
#include "System/RXGameInstance.h"

ARXKnotHanger::ARXKnotHanger()
{
    isCamView = false;
}


void ARXKnotHanger::BeginPlay()
{
	Super::BeginPlay();

    Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    PlayerController = Cast<ARXPlayerController>(Player->GetController());
}

void ARXKnotHanger::HangKnotAction_Implementation()
{
    // Q를 통해서 매듭문자를 다는 액션
    // BP NativeEventFunction 으로 처리
}
void ARXKnotHanger::ChangeToCamView_Implementation()
{
    // isCamView = true;
    // 1초 정도 후에 BP에서 처리
    SwitchToCamera(KnotShowCamera, 0.0f);

    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(true);
    }
    if (Player && KnotShowCamera)
    {
        FVector CameraLocation = KnotShowCamera->GetActorLocation();
        FVector BackwardOffset = -KnotShowCamera->GetActorForwardVector() * 100.0f;
        FVector NewPlayerLocation = CameraLocation + BackwardOffset;
        Player->SetActorLocation(NewPlayerLocation);
    }
}
void ARXKnotHanger::ReturnToPlayerView_Implementation()
{
    isCamView = false;
    SwitchToCamera(Player, 0.0f);

    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(false);
    }
}

void ARXKnotHanger::SwitchToCamera(AActor* NewCamera, float BlendTime) const
{
    if (PlayerController && NewCamera)
    {
        PlayerController->SetViewTargetWithBlend(NewCamera, BlendTime);
    }
}

bool ARXKnotHanger::IsAcquiredKnot_Tutorial()
{
    if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
    {
        return GI->IsItemStatusAcquired("KnotChar_Tutorial");
    }
    return false;
}

bool ARXKnotHanger::IsAcquiredKnot_1F()
{
    if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
    {
        return GI->IsItemStatusAcquired("KnotChar1F_1") &&
            GI->IsItemStatusAcquired("KnotChar1F_2") &&
            GI->IsItemStatusAcquired("KnotChar1F_3");
    }
    return false;
}

bool ARXKnotHanger::IsAcquiredKnot_2F()
{
    if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
    {
        return GI->IsItemStatusAcquired("KnotChar2F_1") &&
            GI->IsItemStatusAcquired("KnotChar2F_2") &&
            GI->IsItemStatusAcquired("KnotChar2F_3");
    }
    return false;
}

void ARXKnotHanger::UseKnotItem(FString KnotHangerType)
{
    if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
    {
        // Tutorial 그룹: KnotChar_Tutorial
        if (KnotHangerType.Equals("Tutorial", ESearchCase::IgnoreCase))
        {
            for (FStatus& Status : GI->ItemStatusArray)
            {
                if (Status.Name == "KnotChar_Tutorial")
                {
                    Status.bIsAcquired = false;
                }
            }
        }
        // 1F 그룹: KnotChar1F_1, KnotChar1F_2, KnotChar1F_3
        else if (KnotHangerType.Equals("1F", ESearchCase::IgnoreCase))
        {
            for (FStatus& Status : GI->ItemStatusArray)
            {
                if (Status.Name == "KnotChar1F_1" ||
                    Status.Name == "KnotChar1F_2" ||
                    Status.Name == "KnotChar1F_3")
                {
                    Status.bIsAcquired = false;
                }
            }
        }
        // 2F 그룹: KnotChar2F_1, KnotChar2F_2, KnotChar2F_3
        else if (KnotHangerType.Equals("2F", ESearchCase::IgnoreCase))
        {
            for (FStatus& Status : GI->ItemStatusArray)
            {
                if (Status.Name == "KnotChar2F_1" ||
                    Status.Name == "KnotChar2F_2" ||
                    Status.Name == "KnotChar2F_3")
                {
                    Status.bIsAcquired = false;
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("UseKnotItem: Unknown KnotHangerType: %s"), *KnotHangerType);
        }
    }
}


