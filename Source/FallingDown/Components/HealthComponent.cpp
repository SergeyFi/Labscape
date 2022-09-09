// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

int32 UHealthComponent::GetHealth() const
{
	return Health;
}
