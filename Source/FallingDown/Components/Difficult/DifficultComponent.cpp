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

	if (GetWorld() && Enabled)
	{
		auto WorldTime = GetWorld()->GetTimeSeconds();
		if (EndTime == 0.0f || WorldTime <= EndTime)
		{
			if (WorldTime >= StartTime)
			{
				ApplyDifficult();
			}
		}
	}
}

void UDifficultComponent::ApplyDifficult()
{
	
}
