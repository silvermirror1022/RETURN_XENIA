// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXPuzzelNotifyWidget.h"
#include "Components/Image.h"

URXPuzzelNotifyWidget::URXPuzzelNotifyWidget(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{

}

void URXPuzzelNotifyWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void URXPuzzelNotifyWidget::UpdatePuzzelLevelImage(int32 LevelID)
{
    if (PuzzelLevelImages.IsValidIndex(LevelID - 1))
    {
        CurLevelImage->SetBrushFromTexture(PuzzelLevelImages[LevelID - 1]);
    }
}
