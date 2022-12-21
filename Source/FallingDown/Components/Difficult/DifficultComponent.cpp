// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/Difficult/DifficultComponent.h"

// Sets default values for this component's properties
UDifficultComponent::UDifficultComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDifficultComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (StartTime <= GetWorld()->GetTimeSeconds())
		{
			ApplyDifficult();
		}
	}
}

void UDifficultComponent::ApplyDifficult()
{
	
}
