// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXPuzzelNotifyWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXPuzzelNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXPuzzelNotifyWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CurLevelImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzel")
	TArray<TObjectPtr<UTexture2D>> PuzzelLevelImages;

	// 퍼즐 스폰메니지 컴포넌트에서 해당 레벨에 맞춰 이미지를 업데이트해주는 함수
	void UpdatePuzzelLevelImage(int32 LevelID);
};
