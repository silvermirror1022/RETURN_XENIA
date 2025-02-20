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

	/*
	 * 메모리 섹션 변수 및 함수
	 * 버튼 활성화 / 비활성화 이미지
	 */

	UFUNCTION(BlueprintCallable)
	void OnCh1BtnPressed(bool bIsKorean);
	UFUNCTION(BlueprintCallable)
	void OnCh2BtnPressed(bool bIsKorean);
	UFUNCTION(BlueprintCallable)
	void OnCh3BtnPressed(bool bIsKorean);
	UFUNCTION(BlueprintCallable)
	void OnCh4BtnPressed(bool bIsKorean);
	UFUNCTION(BlueprintCallable)
	void OnCh5BtnPressed(bool bIsKorean);

private:
	// 모든 버튼의 PressedImage를 리셋하는 함수
	void ResetAllPressedImages() const;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch1_PressedImg_EN;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch1_PressedImg_KR;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch2_PressedImg_EN;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch2_PressedImg_KR;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch3_PressedImg_EN;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch3_PressedImg_KR;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch4_PressedImg_EN;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch4_PressedImg_KR;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch5_PressedImg_EN;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Ch5_PressedImg_KR;
	
};
