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

void ARXKnotHanger::ReturnToPlayerView_Implementation()
{
    SwitchToCamera(Player, 0.0f);

    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(false);
    }
}

void ARXKnotHanger::ChangeToCamView_Implementation()
{
    SwitchToCamera(KnowShowCamera,0.0f);

    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(true);
    }
}

void ARXKnotHanger::SwitchToCamera(AActor* NewCamera, float BlendTime) const
{
    if (PlayerController && NewCamera)
    {
        PlayerController->SetViewTargetWithBlend(NewCamera, BlendTime);
    }
}

