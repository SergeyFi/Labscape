// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/Subcomponents/Subcomponent.h"

void USubcomponent::Init(APawn* NewPlayer)
{
	PlayerPawn = NewPlayer;
	
	OnInit(PlayerPawn);
}

UWorld* USubcomponent::GetWorld() const
{
	if (PlayerPawn)
	{
		return PlayerPawn->GetWorld();
	}

	return nullptr;
}
