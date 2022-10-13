// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/ActorSpawner.h"

// Sets default values for this component's properties
UActorSpawner::UActorSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (ActorClassToSpawn && FMath::RandRange(0.0f, 1.0f) <= SpawnProbability)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ChildActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, GetComponentTransform(), Params);

		if (ChildActor)
		{
			ChildActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

void UActorSpawner::OnRegister()
{
	Super::OnRegister();

	SpawnChild();
}

void UActorSpawner::OnUnregister()
{
	Super::OnUnregister();

	if (ChildActor)
	{
		ChildActor->Destroy();
	}
}

void UActorSpawner::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	if (ChildActor)
	{
		ChildActor->Destroy();
	}
}

void UActorSpawner::SpawnChild()
{
	if (ActorClassToSpawn && GetWorld()->WorldType != EWorldType::Game && GetWorld()->WorldType != EWorldType::PIE)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.bAllowDuringConstructionScript = true;

		ConditionalUpdateComponentToWorld();
		ChildActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, GetComponentTransform(), Params);

		if (ChildActor)
		{
			ChildActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}
