// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/FallingMovementComponent.h"


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


// Called every frame
void UFallingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Movement();

	Falling();
}

void UFallingMovementComponent::AddMovementInput_Implementation(FVector Input)
{
	Input.Normalize();
	InputLast += Input;
}