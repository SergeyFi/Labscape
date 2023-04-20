// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoostComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UBoostComponent::UBoostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBoostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FOVBoost(DeltaTime);
}

void UBoostComponent::Boost()
{
	if (FallingMovement)
	{
		FallingMovement->AdjustVelocityScaler(VelocityScalerMod);
		FallingMovement->AdjustMaxSpeed(MaxSpeedMod);
		bBoost = true;

		if (NiagaraComponent)
		{
			NiagaraComponent->Activate();
		}
	}
}

void UBoostComponent::BoostStop()
{
	if (FallingMovement)
	{
		FallingMovement->AdjustVelocityScaler(-VelocityScalerMod);
		FallingMovement->AdjustMaxSpeed(-MaxSpeedMod);
		bBoost = false;

		if (NiagaraComponent)
		{
			NiagaraComponent->Deactivate();
		}
	}
}

// Called when the game starts
void UBoostComponent::BeginPlay()
{
	Super::BeginPlay();

	FallingMovement = GetOwner()->FindComponentByClass<UFallingMovementComponent>();
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();


	InitFX();
}

void UBoostComponent::FOVBoost(float DeltaTime)
{
	if (Camera)
	{
		auto FOVIncreaseValue = FOVIncreaseSpeed * DeltaTime;
		
		if (bBoost && CurrentFov < FOVAdjust)
		{
			if (CurrentFov + FOVIncreaseValue > FOVAdjust)
			{
				FOVIncreaseValue = FOVAdjust - CurrentFov;
			}

			CurrentFov += FOVIncreaseValue;
			Camera->SetFieldOfView(Camera->FieldOfView + FOVIncreaseValue);
		}
		else if (!bBoost && CurrentFov > 0.0f)
		{
			if (CurrentFov <= DeltaTime)
			{
				Camera->SetFieldOfView(Camera->FieldOfView - CurrentFov);
				CurrentFov = 0.0f;
			}
			else
			{
				Camera->SetFieldOfView(Camera->FieldOfView - FOVIncreaseValue);
				CurrentFov -= FOVIncreaseValue;
			}
		}
	}
}

void UBoostComponent::InitFX()
{
	if (NiagaraSystem)
	{
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached
		(NiagaraSystem, GetOwner()->GetRootComponent(), {}, {}, {0.0f, 0.0f, 0.0f},
		 EAttachLocation::SnapToTarget, false);

		NiagaraComponent->AddLocalOffset(FXOffset);
		NiagaraComponent->Deactivate();
	}
}