// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_EndPosition.h"
#include "RX_SubmapPuzzle_Observer.h"

ARX_SubmapPuzzle_EndPosition::ARX_SubmapPuzzle_EndPosition()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBlock(TEXT("/Game/Designer/Modeling/puzzel/SM_puzzel_A01_puzzel.SM_puzzel_A01_puzzel"));
	if (tempBlock.Succeeded())
	{
		endBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndBlock"));
		endBlock->SetStaticMesh(tempBlock.Object);
	}

	endBlock->OnComponentBeginOverlap.AddDynamic(this, &ARX_SubmapPuzzle_EndPosition::OnOverlapBegin_EP);
}

void ARX_SubmapPuzzle_EndPosition::OnOverlapBegin_EP(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<ACharacter>(OtherActor))
	//{
		observer->ClearPath();
	//}
}
