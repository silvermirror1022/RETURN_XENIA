// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXMapTransitionWidget.generated.h"

/**
 * 
 */

class UImage;
class UTexture2D;

UCLASS()
class RETURN_XENIA_API URXMapTransitionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXMapTransitionWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetMapTransitionImageByName(FName MapName, bool IsKorean);

	// 맵 이름에 따라 이미지 매핑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Images")
	TMap<FName, TObjectPtr<UTexture2D>> KoreanMapImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Images")
	TMap<FName, TObjectPtr<UTexture2D>> EnglishMapImages;

	// 바꿀 이미지
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StageNameImage;
};
