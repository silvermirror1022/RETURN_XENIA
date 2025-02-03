// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RXPuzzelSpawnManageComponent.generated.h"

UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class RETURN_XENIA_API URXPuzzelSpawnManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URXPuzzelSpawnManageComponent();

protected:
	virtual void BeginPlay() override;

public:
    UPROPERTY()
    TObjectPtr<class ARXPlayer> Player;
    
    TMap<int32, TArray<AActor*>> LevelObjectsMap; // 레벨별 해당 엑터 관리

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentLevelID;  // 현재 진행 중인 레벨 ID

    // 퍼즐 타일 초기화
    UFUNCTION()
    void InitializeTileData();

    // 특정 레벨 활성화
    UFUNCTION(BlueprintCallable)
    void ActivateLevel(int32 LevelID);

    // 퍼즐 클리어 종료
	void ClearAllPuzzel();

    // 퍼즐 리셋
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void ResetCurrentLevel();
    void ResetCurrentLevel_Implementation();

    // 퍼즐 힌트 VISIBLE (Used for Only BlindPuzzel)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void VisibleHintTile();
    void VisibleHintTile_Implementation();

    // 퍼즐 힌트타일 VISIBLE (Used for Only BlindPuzzel)
    UFUNCTION(BlueprintCallable)
    void ShowHintTile();

    UPROPERTY(EditAnywhere, Category = "LevelTag")
    TArray<FName> LevelTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PuzzelUI")
    TSubclassOf<class URXPuzzelNotifyWidget> PuzzelNotifyWidgetClass; // 퍼즐 UI 위젯

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<URXPuzzelNotifyWidget> PuzzelNotifyWidget;

    // 퍼즐 UI 위젯 생성 삭제 함수
    void CreatePuzzelNotifyWidget();
    void RemovePuzzelNotifyWidget();
};

