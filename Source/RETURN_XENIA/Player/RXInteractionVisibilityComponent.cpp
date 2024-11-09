// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/RXPlayer.h"
#include "RXDebugHelper.h"
#include "Player/RXInteractionVisibilityComponent.h"

// Sets default values for this component's properties
URXInteractionVisibilityComponent::URXInteractionVisibilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    //사용할려면 만들어놓은 WBP를 ParentWidgetBP 검색후 캐싱해야함.

    // Sphere Component 생성 및 설정
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(this);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Sphere Component의 반지름과 색상 설정
    SphereComponent->SetSphereRadius(220.0f); // 반지름 설정
    SphereComponent->ShapeColor = FColor::Green; // 색상 설정 (디버그용)

    // Widget Component 생성 및 설정
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(this);
    WidgetComponent->SetVisibility(false); // 초기에는 비활성화

    // 크기와 회전을 설정
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 화면에 고정
    WidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f)); // 위젯 크기 설정
    WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // 적절히 조정
}


// Called when the game starts
void URXInteractionVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();

    // WidgetClass가 설정되어 있는 경우에만 적용
    if (WidgetClass)
    {
        WidgetComponent->SetWidgetClass(WidgetClass);
    }

    // Overlap 이벤트 연결
    if (SphereComponent)
    {
        SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &URXInteractionVisibilityComponent::OnSphereBeginOverlap);
        SphereComponent->OnComponentEndOverlap.AddDynamic(this, &URXInteractionVisibilityComponent::OnSphereEndOverlap);

    }
	
}

void URXInteractionVisibilityComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 플레이어인지 확인
    if (OtherActor && OtherActor->IsA<ARXPlayer>())
    {
        if (WidgetComponent)
        {
            WidgetComponent->SetVisibility(true); // 위젯 표시
            //D(FString::Printf(TEXT("done!")));
        }
    }
}

void URXInteractionVisibilityComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // 플레이어인지 확인
    if (OtherActor && OtherActor->IsA<ARXPlayer>())
    {
        if (WidgetComponent)
        {
            WidgetComponent->SetVisibility(false); // 위젯 숨김
            //D(FString::Printf(TEXT("done!")));
        }
        // 플레이어의 감지된 액터 초기화
        if (ARXPlayer* Player = Cast<ARXPlayer>(OtherActor))
        {
            Player->ResetDetectedActors();  // DetectedNPC 및 DetectedTeleportActor를 nullptr로 초기화
        }
    }
}



