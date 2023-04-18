// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Statistic.h"

float UStatistic::GetScore()
{
	return 0.0f;
}

FText UStatistic::GetName()
{
	return Name;
}

FString UStatistic::GetStringValue()
{
	return GetStringValue_Virtual();
}

FString UStatistic::GetStringValue_Virtual()
{
	return "None";
}
