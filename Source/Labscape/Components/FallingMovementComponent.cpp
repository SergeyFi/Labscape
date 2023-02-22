// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/FallingMovementComponent.h"


// Sets default values for this component's properties
UFallingMovementComponent::UFallingMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UFallingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Movement();

	Falling();

	Damping();

	SpeedLimit();

	InputSum= {0.0f, 0.0f, 0.0f};
}

void UFallingMovementComponent::AddMovementInput(FVector Input, float Scale)
{
	if (GetNetMode() == NM_Client)
	{
		SendMovementInputToServer(Input, Scale);
	}

	InputSum += Input * Scale;
}

float UFallingMovementComponent::GetFallingSpeed()
{
	return FMath::Abs(GetOwner()->GetVelocity().Z);
}

// Called when the game starts
void UFallingMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void UFallingMovementComponent::SendMovementInputToServer_Implementation(FVector Input, float Scale)
{	
	InputSum += Input;
}

void UFallingMovementComponent::Falling()
{
	if (FMath::Abs(GetOwner()->GetVelocity().Z) <= MaxFallingSpeed)
	{
		RootComponent->AddForce(GetOwner()->GetActorUpVector() * 1000.0 * -FallingVelocity);
	}
}

void UFallingMovementComponent::Movement()
{
	auto Direction = InputSum;
	Direction.Z = 0.0f;
	
	RootComponent->AddForce(Direction * 1000.0 * MovementSpeed);
}

void UFallingMovementComponent::Damping()
{
	FVector CurrentVelocityNorm = GetOwner()->GetVelocity();
	CurrentVelocityNorm.Normalize();
	
	FVector DampVelocity;
	DampVelocity.X = -CurrentVelocityNorm.X;
	DampVelocity.Y =  -CurrentVelocityNorm.Y;
	
	RootComponent->AddForce(DampVelocity * 1000.0f * MovementDamping);
}

void UFallingMovementComponent::SpeedLimit()
{
	if (GetFallingSpeed() > MaxFallingSpeed)
	{
		auto CurrentVelocity = GetOwner()->GetVelocity();
		CurrentVelocity.Z = -MaxFallingSpeed;
		RootComponent->SetPhysicsLinearVelocity(CurrentVelocity);
	}
}

FVector UFallingMovementComponent::ScaleInput(FVector Input, float Scale)
{
	Scale = FMath::Clamp(Scale, -1.0f, 1.0f);
	Input.Normalize();
	Input *= Scale;

	return Input;
}
