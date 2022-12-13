// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/FallingMovementComponent.h"

// Sets default values for this component's properties
UFallingMovementComponent::UFallingMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFallingMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}


// Called every frame
void UFallingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RootComponent->AddForce(InputLast * 900000.0);
	InputLast = {0.0f, 0.0f, 0.0f};
}

void UFallingMovementComponent::AddMovementInput_Implementation(FVector Input)
{
	Input.Normalize();
	InputLast += Input;
}