// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/Difficult/ChunkDifficult2Component.h"

UChunkDifficult2Component::UChunkDifficult2Component()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UChunkDifficult2Component::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->AddActorLocalRotation({0.0f, RotationSpeed * DeltaTime, 0.0f});
}

void UChunkDifficult2Component::ApplyDifficult()
{
	Super::ApplyDifficult();

	if (GetOwnerRole() == ROLE_Authority)
	{
		auto Sign = -1;

		if (FMath::RandBool())
		{
			Sign = 1;
		}
	
		RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed) * Sign;

		SetRotationSpeedClient(RotationSpeed);

		SetComponentTickEnabled(true);
	}

	
}

void UChunkDifficult2Component::SetRotationSpeedClient_Implementation(float Speed)
{
	RotationSpeed = Speed;

	SetComponentTickEnabled(true);
}
