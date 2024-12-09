// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RXPuzzelStartComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

URXPuzzelStartComponent::URXPuzzelStartComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URXPuzzelStartComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

/*
 * Mapping Context Change 는 블루프린트에서 구현 
 */

void URXPuzzelStartComponent::StartPuzzelMode_Implementation()
{
	// StartPos 태그가 있는 액터를 검색
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PuzzelStartPos"), TaggedActors);

	if (TaggedActors.Num() > 0)
	{
		// 첫 번째 태그 액터의 위치로 이동
		AActor* StartPosActor = TaggedActors[0];
		if (StartPosActor && Player)
		{
			Player->SetActorLocation(StartPosActor->GetActorLocation());
		}
	}

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

void URXPuzzelStartComponent::EndPuzzelMode_Implementation()
{
	// StartPos 태그가 있는 액터를 검색
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PuzzelClearPos"), TaggedActors);

	if (TaggedActors.Num() > 0)
	{
		// 첫 번째 태그 액터의 위치로 이동
		AActor* StartPosActor = TaggedActors[0];
		if (StartPosActor && Player)
		{
			Player->SetActorLocation(StartPosActor->GetActorLocation());
		}
	}

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

	}
}
