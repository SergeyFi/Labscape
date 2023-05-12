// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickable/PickablePoint.h"
#include "Components/Statistic/Classes/StatPoints.h"

void APickablePoint::OnGather(AActor* PlayerTarget)
{
	Super::OnGather(PlayerTarget);

	GetStatistic<UStatPoints>(PlayerTarget)->PointsPicked += 1;
}
