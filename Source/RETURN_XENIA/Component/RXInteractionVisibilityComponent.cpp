// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/RXInteractionVisibilityComponent.h"
#include "RXDebugHelper.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/RXPlayer.h"

URXInteractionVisibilityComponent::URXInteractionVisibilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    bIsBlackInteractionPrompt = false;

    //사용할려면 만들어놓은 WBP를 ParentWidgetBP 검색후 캐싱해야함.

    // Box Component 생성 및 설정
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(this);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Box Component의 크기 설정
    BoxComponent->SetBoxExtent(FVector(220.f, 220.f, 220.f)); // 박스 크기 설정

    // Widget Component 생성 및 설정
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(this);
    WidgetComponent->SetVisibility(false); // 초기에는 비활성화

    // 크기와 회전 설정
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 화면에 고정
    WidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f)); // 위젯 크기 설정
    WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // 적절히 조정
}


void URXInteractionVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();

    // WidgetClass가 설정되어 있는 경우에만 적용 -> 흰색
    if (bIsBlackInteractionPrompt && WidgetClass2)
    {
        WidgetComponent->SetWidgetClass(WidgetClass2); // 검정색 프롬프트 적용
    }
    else if (WidgetClass)
    {
        WidgetComponent->SetWidgetClass(WidgetClass);  // 흰색 프롬프트 적용
    }

    if (BoxComponent) // Overlap 이벤트 연결
    {
        BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &URXInteractionVisibilityComponent::OnBoxBeginOverlap);
        BoxComponent->OnComponentEndOverlap.AddDynamic(this, &URXInteractionVisibilityComponent::OnBoxEndOverlap);
    }
}

void URXInteractionVisibilityComponent::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 플레이어인지 확인
    if (OtherActor && OtherActor->IsA<ARXPlayer>())
    {
        //D(FString::Printf(TEXT("done!")));
        if (WidgetComponent)
        {
            WidgetComponent->SetVisibility(true); // 위젯 표시
            //D(FString::Printf(TEXT("done!!")));
        }
    }
}

void URXInteractionVisibilityComponent::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void URXInteractionVisibilityComponent::SetInteractionVisibility(bool bIsVisible)
{
    if (WidgetComponent)
    {
        if(bIsVisible)
        {
            WidgetComponent->SetVisibility(true); // 위젯 보이게
        }
        else
        {
            WidgetComponent->SetVisibility(false); // 위젯 숨김
        }
    }
}



