// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/Difficult/ChunkDifficult1Component.h"


UChunkDifficult1Component::UChunkDifficult1Component()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UChunkDifficult1Component::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->AddActorLocalRotation({0.0f, RotationSpeed * DeltaTime * FMath::Sign(MaxZRotation), 0.0f});

	CurrentZRotation += RotationSpeed * DeltaTime;

	if (CurrentZRotation >= FMath::Abs(MaxZRotation))
	{
		SetComponentTickEnabled(false);
	}
}

void UChunkDifficult1Component::ApplyDifficult()
{
	Super::ApplyDifficult();

	MaxZRotation = FMath::RandRange(MinRotation, MaxRotation);

	SetComponentTickEnabled(true);
}
