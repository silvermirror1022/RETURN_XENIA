// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RXPuzzelEventManageComponent.h"
#include "GameFramework/PlayerController.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Component/RXPuzzelSpawnManageComponent.h"
#include "GameFramework/Actor.h"
#include "Player/RXPlayerController.h"
#include "Camera/CameraActor.h"
#include "Components/MeshComponent.h"

URXPuzzelEventManageComponent::URXPuzzelEventManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URXPuzzelEventManageComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	PlayerController = Cast<ARXPlayerController>(Player->GetController());
}

/*
 * Mapping Context Change 는 블루프린트에서 구현 
 */

void URXPuzzelEventManageComponent::StartPuzzelMode_Implementation()
{
	// 플레이어 퍼즐 시작 위치로 이동
	Player->MoveToTagLocation("PuzzelStartPos", 30.0f);

	if(UMeshComponent* MeshComponent=Player->FindComponentByClass<UMeshComponent>())
	{
		// 퍼즐모드시 플레이어 그림자 비활성화
		MeshComponent->SetCastShadow(false);
	}

	// 카메라 전환
	SwitchToCamera(PuzzelModeCamera, 0.0f);
}

void URXPuzzelEventManageComponent::EndPuzzelMode_Implementation()
{
	// 플레이어 퍼즐 종료 위치로 이동
	Player->MoveToTagLocation("PuzzelClearPos", 30.0f);

	if (UMeshComponent* MeshComponent = Player->FindComponentByClass<UMeshComponent>())
	{
		// 퍼즐모드시 플레이어 그림자 활성화
		MeshComponent->SetCastShadow(true);
	}

	// 원래 플레이어 카메라로 복귀
	SwitchToCamera(Player, 0.0f);

	// 소유자에서 URXPuzzelSpawnManageComponent 가져오기
	if (AActor* ComponentOwner = GetOwner())
	{
		if (URXPuzzelSpawnManageComponent* SpawnManageComponent = ComponentOwner->FindComponentByClass<URXPuzzelSpawnManageComponent>())
		{
			SpawnManageComponent->ClearAllPuzzel();
		}
	}
}
void URXPuzzelEventManageComponent::SwitchToCamera(AActor* NewCamera, float BlendTime) const
{
	if (PlayerController && NewCamera)
	{
		PlayerController->SetViewTargetWithBlend(NewCamera, BlendTime);
	}
}
