// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Statistic/Statistic.h"
#include "StatDistance.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API UStatDistance : public UStatistic
{
	GENERATED_BODY()

public:

	virtual float GetScore() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic", SaveGame)
	float FallingDistance;

private:

	float ScoreCoefficient = 0.1f;
};
