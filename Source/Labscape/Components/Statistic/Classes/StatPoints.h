// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Statistic/Statistic.h"
#include "StatPoints.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API UStatPoints : public UStatistic
{
	GENERATED_BODY()

public:

	virtual float GetScore() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic", SaveGame)
	int32 PointsPicked;

private:

	float ScoreForPoint = 10.0f;
};
