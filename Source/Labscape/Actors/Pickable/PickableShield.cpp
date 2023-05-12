// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickable/PickableShield.h"

#include "Components/ShieldComponent.h"
#include "Components/Statistic/Classes/StatShield.h"

void APickableShield::OnGather(AActor* PlayerTarget)
{
	Super::OnGather(PlayerTarget);

	PlayerTarget->FindComponentByClass<UShieldComponent>()->AddShieldCell(1);

	GetStatistic<UStatShield>(PlayerTarget)->ShieldsPicked += 1;
}
