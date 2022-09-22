// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/UI/UIComponent.h"

// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UUIComponent::InitSubmodules()
{
	for (auto& SubComponent : Subcomponents)
	{
		if (SubComponent)
		{
			auto Pawn = GetOwner<APawn>();

			if (Pawn)
			{
				SubComponent->Init(Pawn->GetController<APlayerController>());
			}
		}
	}
}

// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	InitSubmodules();
}
