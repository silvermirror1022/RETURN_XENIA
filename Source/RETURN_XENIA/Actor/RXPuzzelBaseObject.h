// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXPuzzelBaseObject.generated.h"

UCLASS()
class RETURN_XENIA_API ARXPuzzelBaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ARXPuzzelBaseObject();

protected:
	virtual void BeginPlay() override;

public:
	// 모든 퍼즐의 오브젝트들은 이 클래스를 상속받아서 블루프린트로 파생
	// 이 함수는 플레이어가 퍼즐을 리셋할 때 각각 모두 호출하게 되는 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetObjectState();
	virtual void ResetObjectState_Implementation();

};
