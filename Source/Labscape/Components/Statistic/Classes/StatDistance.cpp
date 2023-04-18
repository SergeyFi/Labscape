// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatDistance.h"

UStatDistance::UStatDistance()
{
	Name = FText::FromString("Distance");
}

float UStatDistance::GetScore()
{
	return FallingDistance * ScoreCoefficient;
}

FString UStatDistance::GetStringValue_Virtual()
{
	return FString::FromInt(FallingDistance);
}
