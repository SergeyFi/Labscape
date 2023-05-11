// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickable/PickablePoint.h"

#include "Components/Statistic/Classes/StatPoints.h"
#include "FunctionLibraries/BlueprintAssistFunctionLibrary.h"

void APickablePoint::OnGather(AActor* PlayerTarget)
{
	Super::OnGather(PlayerTarget);

	auto StatPoints = Cast<UStatPoints>(UBlueprintAssistFunctionLibrary::GetStatistic(PlayerTarget, UStatPoints::StaticClass()));

	if (StatPoints)
	{
		StatPoints->PointsPicked += 1;
	}

	UBlueprintAssistFunctionLibrary::GetScoreComponent(PlayerTarget)->AddScore(Score);
}
