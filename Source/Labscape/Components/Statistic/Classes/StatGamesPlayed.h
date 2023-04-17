// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Statistic/Statistic.h"
#include "StatGamesPlayed.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API UStatGamesPlayed : public UStatistic
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic", SaveGame)
	int32 GamesPlayed;
};
