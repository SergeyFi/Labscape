// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Statistic.generated.h"


UCLASS(Abstract, BlueprintType, HideDropdown = "true")
class LABSCAPE_API UStatistic : public UObject
{
	GENERATED_BODY()

public:

	virtual float GetScore();

	UFUNCTION(BlueprintPure, Category = "Statistic")
	FText GetName();

	UFUNCTION(BlueprintPure, Category = "Statistic")
	FString GetStringValue();

protected:

	UPROPERTY(EditDefaultsOnly)
	FText Name = FText::FromString("None");

	virtual FString GetStringValue_Virtual();
};
