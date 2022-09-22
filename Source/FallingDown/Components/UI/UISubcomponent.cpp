// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Components/UI/UISubcomponent.h"

void UUISubcomponent::Init(APlayerController* NewPlayer)
{
	PlayerOwner = NewPlayer;
	
	OnInit(PlayerOwner);
}

UWorld* UUISubcomponent::GetWorld() const
{
	if (PlayerOwner)
	{
		return PlayerOwner->GetWorld();
	}

	return nullptr;
}
