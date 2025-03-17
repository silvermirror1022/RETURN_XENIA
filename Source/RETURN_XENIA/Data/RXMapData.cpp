// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RXMapData.h"

const FRXMapDataInfo* URXMapData::FindMapDataByName(const FName& InputMapName) const
{
    for (const FRXMapDataInfo& MapDataEntry : MapData)
    {
        if (MapDataEntry.MapName == InputMapName)
        {
            return &MapDataEntry;
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Can't find MapData for MapName [%s]"), *InputMapName.ToString());
    return nullptr;
}