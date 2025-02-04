// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RXLevelTeleportActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/RXGameInstance.h"
#include "RXDebugHelper.h"

ARXLevelTeleportActor::ARXLevelTeleportActor()
{

    // Sphere Component CDO ���� �� ����
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


    // Sphere Component�� �������� ���� ����
    SphereComponent->SetSphereRadius(80.0f); // ������ ����
    SphereComponent->ShapeColor = FColor::Green; // ���� ���� (����׿�)

}

void ARXLevelTeleportActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARXLevelTeleportActor::TeleportToOtherLevel_Implementation()
{
    // ���� �ν��Ͻ��� �����Ͽ� DestinationTag�� ����
    if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
    {
        GameInstance->SetDestinationTag(DestinationTag);
    }

    // �÷��̾� ��Ʈ�ѷ� �����ͼ� �Է� ��Ȱ��ȭ
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(true);  // �̵� �Է� ����
        //PlayerController->SetIgnoreLookInput(true);  // ī�޶� ȸ�� �Է� ����
    }

    // ���� ���� ��ȯ
    // UGameplayStatics::OpenLevel(this, NextLevelName);

    if (NextLevelName.IsNone())
    {
        // �±װ� �������� �ʴ� ��Ȳ ����ó��
        UE_LOG(LogTemp, Warning, TEXT("NextLevelName is not set!"));
        return;
    }

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
    LatentInfo.Linkage = 0;
    LatentInfo.UUID = __LINE__;

    UGameplayStatics::LoadStreamLevel(this, NextLevelName, true, false, LatentInfo);
}

void ARXLevelTeleportActor::OnLevelLoaded() const
{
    UE_LOG(LogTemp, Log, TEXT("Level %s Loaded Successfully"), *NextLevelName.ToString());
    UGameplayStatics::UnloadStreamLevel(this, *GetWorld()->GetMapName(), FLatentActionInfo(), false);
}



