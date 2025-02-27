// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXKnotHanger.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RXPlayer.h"
#include "Player/RXPlayerController.h"
#include "Camera/CameraActor.h"

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
    SwitchToCamera(KnotShowCamera,0.0f);

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

