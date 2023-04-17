// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatDistance.h"

float UStatDistance::GetScore()
{
	return FallingDistance * ScoreCoefficient;
}
