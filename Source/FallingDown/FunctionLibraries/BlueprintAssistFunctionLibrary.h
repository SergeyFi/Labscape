// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintAssistFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum EBPNetMode
{
	None     UMETA(DisplayName = "None"),
	Client     UMETA(DisplayName = "Client"),
	DedicatedServer    UMETA(DisplayName = "DedicatedServer"),
	ListenServer     UMETA(DisplayName = "ListenServer"),
	Standalone     UMETA(DisplayName = "Standalone")
};

/**
 * 
 */
UCLASS()
class FALLINGDOWN_API UBlueprintAssistFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Blueprint assist", meta = (WorldContext = "WorldContextObject"))
	static EBPNetMode GetNetMode(UObject* WorldContextObject);
};
