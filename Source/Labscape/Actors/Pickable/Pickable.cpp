// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickable/Pickable.h"
#include "Players/PlayerBase.h"

// Sets default values
APickable::APickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetSphereRadius(230.0f);
	SphereCollision->SetCollisionProfileName("OverlapAll");
}

// Called when the game starts or when spawned
void APickable::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APickable::OnPickableOverlap);
}

void APickable::OnGather(AActor* PlayerTarget)
{
	PlayGatherSound();
}

void APickable::OnPickableOverlap(AActor* This, AActor* Other)
{
	if (Cast<APlayerBase>(Other))
	{
		Target = Other;
		SetActorTickEnabled(true);
		OnGather(Target);
	}
}

void APickable::PlayGatherSound()
{
	if (GatherSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), GatherSound);
	}
}

// Called every frame
void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target && !Target->IsPendingKillPending())
	{
		GatheringTime += DeltaTime;
		
		auto TargetLocation = Target->GetActorLocation() - Target->GetActorUpVector() * 500.0f;
		
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, GatheringSpeed));

		SetActorRelativeScale3D(FMath::VInterpTo(GetActorRelativeScale3D(), {0.0f, 0.0f, 0.0f}, DeltaTime, GatheringSpeed));

		if (FVector::Distance(GetActorLocation(), TargetLocation) <= GatherDistance || GatheringTime >= GatheringTimeMax)
		{
			Destroy();
		}
	}
}
