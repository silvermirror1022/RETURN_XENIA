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

	// 해당 함수는 M Key를 통해 맵메인메뉴를 킬 때 맵 매뉴로 초기화해주는 함수
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitToGameMapMenu();
	virtual void InitToGameMapMenu_Implementation();

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

	/*
	 * 아이템과 파피루스 아이템 슬롯에 대한 중재자 함수
	 */

	void ClearPapyrusSelection();
	void ClearInventorySelection();

private:
	// 아이템 파피루스 아이템 위젯 참조 변수
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URXPapyrusSlotsWidget> WBP_PapyrusSlotsWidget;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URXInventorySlotsWidget> WBP_InventorySlotsWidget;

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
