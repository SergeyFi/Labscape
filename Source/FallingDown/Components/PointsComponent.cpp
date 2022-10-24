// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/PointsComponent.h"

// Sets default values for this component's properties
UPointsComponent::UPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPointsComponent::AddPoints(int32 Count)
{
	Points += Count;

	OnPointsUpdated.Broadcast(Points);

	UpdatePoints(Points);
}

int32 UPointsComponent::GetPoints()
{
	return Points;
}

void UPointsComponent::UpdatePoints_Implementation(int32 Count)
{
	Points = Count;
	OnPointsUpdated.Broadcast(Points);
}
