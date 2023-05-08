// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/Health/HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::AddDamage(int32 Damage)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		if (!bGodMode && Health)
		{
			if (!bSuppressDamage)
			{
				Health -= Damage;

				if (Health <= 0)
				{
					Health = 0;
				
					OnHealthEnd.Broadcast();
				}

				OnDamage.Broadcast(Damage);
			}
			else
			{
				OnDamageSuppress.Broadcast(Damage);
			}
		}
	}
}

int32 UHealthComponent::GetHealth() const
{
	return Health;
}

bool UHealthComponent::HealthIsOver()
{
	return Health == 0;
}

void UHealthComponent::Kill()
{
	if (!bGodMode)
	{
		OnDamage.Broadcast(Health);
		OnHealthEnd.Broadcast();
		Health = 0;
	}
}

void UHealthComponent::SuppressDamage(bool bSuppress)
{
	bSuppressDamage = bSuppress;
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
