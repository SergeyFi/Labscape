// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/ReplicatedComponent.h"

// Sets default values for this component's properties
UReplicatedComponent::UReplicatedComponent()
{
	SetIsReplicatedByDefault(true);
}

void UReplicatedComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

