// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Statistic.h"
#include "GameFramework/SaveGame.h"
#include "StatisticSaveGame.generated.h"


USTRUCT()
struct FStatisticSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TSubclassOf<UStatistic> StatClass;

	UPROPERTY()
	TArray<uint8> ByteData;
};

/**
 * 
 */
UCLASS()
class LABSCAPE_API UStatisticSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	TArray<FStatisticSaveData> Statistics;
};
