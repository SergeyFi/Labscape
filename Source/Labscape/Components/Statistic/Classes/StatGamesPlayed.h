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

	UStatGamesPlayed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic", SaveGame)
	int32 GamesPlayed;

protected:

	virtual FString GetStringValue_Virtual() override;
};
