// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_Rule.h"
#include "Kismet/GameplayStatics.h"
#include "RX_SubmapPuzzle_Observer.h"

// Sets default values
ARX_SubmapPuzzle_Rule::ARX_SubmapPuzzle_Rule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make main body
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBlock(TEXT("/Game/Designer/Modeling/puzzel/SM_puzzel_A01_puzzel.SM_puzzel_A01_puzzel"));
	if (tempBlock.Succeeded())
	{
		block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
		block->SetStaticMesh(tempBlock.Object);
		RootComponent = block;
	}

	block->OnComponentBeginOverlap.AddDynamic(this, &ARX_SubmapPuzzle_Rule::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ARX_SubmapPuzzle_Rule::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_Observer::StaticClass(), tempArray);
	observer = Cast<ARX_SubmapPuzzle_Observer>(tempArray[0]);
}

// Called every frame
void ARX_SubmapPuzzle_Rule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Begin Overlap Action
void ARX_SubmapPuzzle_Rule::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == observer->player)
	{
		if (isAlreadyTriggered)
		{
			// Return To Start Position
			observer->WrongPath();
		}
		else
		{
			isAlreadyTriggered = true;
		}
	}
}

