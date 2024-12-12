// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RXPuzzelEventManageComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Component/RXPuzzelSpawnManageComponent.h"
#include "GameFramework/Actor.h"

URXPuzzelEventManageComponent::URXPuzzelEventManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URXPuzzelEventManageComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
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

	if(USpringArmComponent* SpringArmComponent = Player->FindComponentByClass<USpringArmComponent>())
	{
		// 플레이어 컨트롤 로테이션 비활성화
		SpringArmComponent->bUsePawnControlRotation = false;

		// 카메라가 회전하지 않도록 설정
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bInheritRoll = false;

		// 스프링 암 길이 변경
		SpringArmComponent->TargetArmLength = 900.f;

		// 스프링 암의 로테이션 조정 (Y축 -90도)
		FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
		NewRotation.Pitch = -90.f;
		SpringArmComponent->SetRelativeRotation(NewRotation);
	}
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

	if (USpringArmComponent* SpringArmComponent = Player->FindComponentByClass<USpringArmComponent>())
	{
		// 플레이어 컨트롤 로테이션 복원
		SpringArmComponent->bUsePawnControlRotation = true;

		// 카메라 회전 속성 복원
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritYaw = true;
		SpringArmComponent->bInheritRoll = true;

		// 스프링 암 길이 복원 
		SpringArmComponent->TargetArmLength = 500.f; 

		// 스프링 암의 로테이션 복원
		FRotator DefaultRotation = FRotator::ZeroRotator;
		SpringArmComponent->SetRelativeRotation(DefaultRotation);

		// 이 컴포넌트를 소유한 소유자액터를 찾고, PuzzelSpawnManageComponent의 퍼즐클리어함수호출.
		if(AActor* ComponentOwner = GetOwner())
		{
			if(URXPuzzelSpawnManageComponent* SpawnManageComponent = ComponentOwner->FindComponentByClass<URXPuzzelSpawnManageComponent>())
			{
				SpawnManageComponent->ClearAllPuzzel(); // 해당 퍼즐 삭제.
			}
			
		}
	}
}
