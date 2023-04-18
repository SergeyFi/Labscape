// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/FunctionLibraries/BlueprintAssistFunctionLibrary.h"
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

bool UBlueprintAssistFunctionLibrary::IsLocalPlayer(UObject* WorldContextObject)
{
	auto NetMode = GetNetMode(WorldContextObject);

	if (NetMode == EBPNetMode::Client || NetMode == EBPNetMode::Standalone)
	{
		return true;
	}
	
	return false;
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

UScoreComponent* UBlueprintAssistFunctionLibrary::GetScoreComponent(AActor* Target)
{
	auto Pawn = Cast<APawn>(Target);

	if (Pawn)
	{
		auto Controller = Pawn->Controller;

		if (Controller)
		{
			auto ScoreComponent = Pawn->Controller->FindComponentByClass<UScoreComponent>();

			return ScoreComponent;
		}
	}

	return nullptr;
}

UStatisticComponent* UBlueprintAssistFunctionLibrary::GetStatisticComponent(AActor* PlayerPawn)
{
	auto Pawn = Cast<APawn>(PlayerPawn);

	if (Pawn)
	{
		return Pawn->GetController()->FindComponentByClass<UStatisticComponent>();
	}

	return nullptr;
}

UStatistic* UBlueprintAssistFunctionLibrary::GetStatistic(AActor* PlayerPawn, TSubclassOf<UStatistic> StatisticClass, const EStatisticType Type)
{
	auto StatComp = GetStatisticComponent(PlayerPawn);

	if (StatComp)
	{
		return StatComp->GetStatistic(StatisticClass, Type);
	}

	return nullptr;
}
