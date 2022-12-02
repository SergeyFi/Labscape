// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/UI/UIComponent.h"

// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUIComponent::SetVisibility(bool bVisibility)
{
	for (auto& SubComponent : Subcomponents)
	{
		SubComponent->SetVisibility(bVisibility);
	}
}


void UUIComponent::InitSubmodules()
{
	for (auto& SubComponent : Subcomponents)
	{
		SubComponent->Init(GetOwner<APawn>());
	}
}

// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetNetMode() == ENetMode::NM_Standalone || GetOwner()->GetNetMode() == ENetMode::NM_Client)
	{
		InitSubmodules();
	}
}
