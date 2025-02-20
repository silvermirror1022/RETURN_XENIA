// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXMainMenuWidget.generated.h"

class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	URXMainMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UImage> ItemInfoImage; // 아이템정보에서 참조할 이미지

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UImage> Img_ItemDesc_KR; // 아이템 설명(한국어 544*197)

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UImage> Img_ItemDesc_EN; // 아이템 설명(영어 544*189)

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UButton> Btn_NoteDesc; // 노트 아이템 설명창 버튼

	

	
};
