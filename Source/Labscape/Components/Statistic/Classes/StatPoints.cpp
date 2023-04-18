// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatPoints.h"

UStatPoints::UStatPoints()
{
	Name = FText::FromString("Points");
}

float UStatPoints::GetScore()
{
	return ScoreForPoint * PointsPicked;
}

FString UStatPoints::GetStringValue_Virtual()
{
	return FString::FromInt(PointsPicked);
}
