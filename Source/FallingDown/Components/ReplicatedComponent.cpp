// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/ReplicatedComponent.h"

// Sets default values for this component's properties
UReplicatedComponent::UReplicatedComponent()
{
	SetIsReplicated(true);
}

void UReplicatedComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

