// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShieldComponent.h"

// Sets default values for this component's properties
UShieldComponent::UShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UShieldComponent::Enable()
{
	if (!bShieldEnabled && ShieldCells > 0)
	{
		ShieldMesh->SetVisibility(true);
		HealthComponent->SuppressDamage(true);
		bShieldEnabled = true;
		ShieldCells -= 1;
		GetWorld()->GetTimerManager().SetTimer(TimerShield, this, &UShieldComponent::Disable, ShieldDuration);
	}
}

void UShieldComponent::Disable()
{
	ShieldMesh->SetVisibility(false);
	HealthComponent->SuppressDamage(false);
	bShieldEnabled = false;
}

void UShieldComponent::AddShieldCell(int32 Count)
{
	if (Count > 0)
	{
		ShieldCells += Count;

		if (ShieldCells > ShieldCellsMax)
		{
			ShieldCells = ShieldCellsMax;
		}
	}
}

// Called when the game starts
void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();

	if (HealthComponent && Mesh && Material)
	{
		CreateShieldMesh();
	}
}

void UShieldComponent::CreateShieldMesh()
{
	ShieldMesh = NewObject<UStaticMeshComponent>(GetOwner());
	ShieldMesh->SetStaticMesh(Mesh);
	ShieldMesh->SetMaterial(0, Material);
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldMesh->SetupAttachment(this);
	ShieldMesh->SetVisibility(false);
	ShieldMesh->RegisterComponent();
}
