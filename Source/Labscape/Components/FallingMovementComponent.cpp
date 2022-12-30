// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/FallingMovementComponent.h"


// Sets default values for this component's properties
UFallingMovementComponent::UFallingMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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

void UFallingMovementComponent::SendMovementInputToServer_Implementation(FVector Input)
{
	Input.Normalize();
	InputLast += Input;
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
	RootComponent->AddForce(InputLast * 1000.0 * MovementSpeed);
	InputLast = {0.0f, 0.0f, 0.0f};
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


// Called every frame
void UFallingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Movement();

	Falling();

	Damping();

	SpeedLimit();
}

void UFallingMovementComponent::AddMovementInput(FVector Input)
{
	if (GetNetMode() == NM_Standalone)
	{
		Input.Normalize();
		InputLast += Input;
		return;
	}
	
	if (GetNetMode() == NM_Client)
	{
		SendMovementInputToServer(Input);
		Input.Normalize();
		InputLast += Input;
	}
}