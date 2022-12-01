// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Players/PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority())
	{
		ScoreComponent = NewController->FindComponentByClass<UScoreComponent>();
	}
}

void APlayerBase::AddScoreForMovement(float DeltaTime)
{
	if (ScoreComponent)
	{
		auto PlayerZVelocity = GetVelocity().Z;

		if (PlayerZVelocity < 0.0f)
		{
			ScoreComponent->AddScore(FMath::Abs(PlayerZVelocity) * DeltaTime * PlayerMovementScoreScale);
		}
	}
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddScoreForMovement(DeltaTime);
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

