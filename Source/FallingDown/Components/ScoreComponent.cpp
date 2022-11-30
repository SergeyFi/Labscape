// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/ScoreComponent.h"


// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoreComponent::AddScore(float Count)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Score += Count;
	}
}

float UScoreComponent::GetScore()
{
	return Score;
}

void UScoreComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UScoreComponent, Score);
}
