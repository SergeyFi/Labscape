// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/Difficult/ChunkDifficult2Component.h"

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

	auto Sign = -1;

	if (FMath::RandBool())
	{
		Sign = 1;
	}
	
	RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed) * Sign;

	SetComponentTickEnabled(true);
}
