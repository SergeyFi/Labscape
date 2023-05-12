// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatShield.h"

UStatShield::UStatShield()
{
	Name = FText::FromString("Shields");
}

float UStatShield::GetScore()
{
	return ScoreForShield * ShieldsPicked;
}

FString UStatShield::GetStringValue_Virtual()
{
	return FString::FromInt(ShieldsPicked);
}
