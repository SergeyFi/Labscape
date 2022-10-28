// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/FunctionLibraries/BlueprintAssistFunctionLibrary.h"

EBPNetMode UBlueprintAssistFunctionLibrary::GetNetMode(UObject* WorldContextObject)
{
	auto Actor = Cast<AActor>(WorldContextObject);

	if (Actor)
	{
		if (Actor->GetNetMode() == ENetMode::NM_Client)
		{
			return EBPNetMode::Client;
		}
		
		if (Actor->GetNetMode() == ENetMode::NM_Standalone)
		{
			return EBPNetMode::Standalone;
		}
		
		if (Actor->GetNetMode() == ENetMode::NM_DedicatedServer)
		{
			return EBPNetMode::DedicatedServer;
		}
		
		if (Actor->GetNetMode() == ENetMode::NM_ListenServer)
		{
			return EBPNetMode::ListenServer;
		}
	}

	return EBPNetMode::None;
}
