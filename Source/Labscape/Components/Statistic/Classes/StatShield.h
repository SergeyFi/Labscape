// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Statistic/Statistic.h"
#include "StatShield.generated.h"

/**
 * 
 */
UCLASS()
class LABSCAPE_API UStatShield : public UStatistic
{
	GENERATED_BODY()

public:

	UStatShield();

	virtual float GetScore() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic", SaveGame)
	int32 ShieldsPicked;

protected:

	virtual FString GetStringValue_Virtual() override;

private:

	float ScoreForShield= 400.0f;
};
