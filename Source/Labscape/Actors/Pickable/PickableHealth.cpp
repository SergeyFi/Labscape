// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickable/PickableHealth.h"

#include "Components/Health/HealthComponent.h"

void APickableHealth::OnGather(AActor* PlayerTarget)
{
	Super::OnGather(PlayerTarget);

	PlayerTarget->FindComponentByClass<UHealthComponent>()->AddHealth(1);
}
