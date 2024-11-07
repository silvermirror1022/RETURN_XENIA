// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXLevelTeleportActor.generated.h"

UCLASS()
class RETURN_XENIA_API ARXLevelTeleportActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ARXLevelTeleportActor();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	// 카테고리 TeleportSettings 검색 후 블루프린트 에디터에서 설정해줘야함.
	UPROPERTY(EditAnywhere, Category="TeleportSettings")
	TObjectPtr<class APlayerStart> TargetLocation; // 같은 레벨 내에서 이동시킬 타겟 로케이션

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportSettings")
	FName NextLevelName;  // 다른레벨로의 이동

	
};
