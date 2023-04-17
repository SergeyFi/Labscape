// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/Classes/StatPoints.h"

float UStatPoints::GetScore()
{
	return ScoreForPoint * PointsPicked;
}
