// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXSavingGameWidget.generated.h"

class UImage;
class UTexture2D;

/**
 * 저장 중 화면 표시 위젯
 */

UCLASS()
class RETURN_XENIA_API URXSavingGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXSavingGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Image Switching")
	TObjectPtr<UImage> Image_LoadingCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "Image Switching")
	TObjectPtr<UImage> Image_LoadingText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image Switching")
	TArray<TObjectPtr<UTexture2D>> LoadingCircleTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image Switching")
	TArray<TObjectPtr<UTexture2D>> LoadingTextTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image Switching")
	float LoadingCircleDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image Switching")
	float LoadingTextDuration = 1.5f;

private:
	// 현재 표시 중인 인덱스
	int32 CurrentIndexCircle = 0;
	int32 CurrentIndexText = 0;

	// 타이머 핸들
	FTimerHandle TimerHandleCircle;
	FTimerHandle TimerHandleText;

	// 각각의 이미지 업데이트 함수
	void UpdateLoadingCircleImage();
	void UpdateLoadingTextImage();
};
