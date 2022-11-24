// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/FunctionLibraries/BlueprintAssistFunctionLibrary.h"

#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"

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

UUserWidget* UBlueprintAssistFunctionLibrary::GetParentUserWidget(UObject* WorldContextObject)
{
	UUserWidget* UserWidget = nullptr;

	auto Widget = Cast<UWidget>(WorldContextObject);
	
	if (Widget)
	{
		auto Parent = Widget->GetParent();
	
		if (Parent)
		{
			auto Outer = Parent->GetOuter();

			while (Outer && UserWidget == nullptr)
			{
				UserWidget = Cast<UUserWidget>(Outer);
				Outer = Outer->GetOuter();
			}
		}
	}
	
	return UserWidget;
}
