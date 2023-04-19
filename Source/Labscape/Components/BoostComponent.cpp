// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoostComponent.h"

// Sets default values for this component's properties
UBoostComponent::UBoostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UBoostComponent::Boost()
{
	if (FallingMovement)
	{
		FallingMovement->AdjustVelocityScaler(VelocityScalerMod);
		FallingMovement->AdjustMaxSpeed(MaxSpeedMod);
	}
}

void UBoostComponent::BoostStop()
{
	if (FallingMovement)
	{
		FallingMovement->AdjustVelocityScaler(-VelocityScalerMod);
		FallingMovement->AdjustMaxSpeed(-MaxSpeedMod);
	}
}


// Called when the game starts
void UBoostComponent::BeginPlay()
{
	Super::BeginPlay();

	FallingMovement = GetOwner()->FindComponentByClass<UFallingMovementComponent>();
}
