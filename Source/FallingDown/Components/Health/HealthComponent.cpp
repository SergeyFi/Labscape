// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/Health/HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

void UHealthComponent::AddDamage(int32 Damage)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Health -= Damage;

		if (Health < 0)
		{
			Health = 0;
		}

		OnHealthCountChanged.Broadcast(Health);

		UpdateHealthOnClient(Health);
	}
}

int32 UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetNetMode() != ENetMode::NM_Client)
	{
		for (auto& Subcomponent : Subcomponents)
		{
			Subcomponent->Init(GetOwner<APawn>());
		}
	}
}

void UHealthComponent::UpdateHealthOnClient_Implementation(int32 HealthCount)
{
	Health = HealthCount;
	OnHealthCountChanged.Broadcast(Health);
}
