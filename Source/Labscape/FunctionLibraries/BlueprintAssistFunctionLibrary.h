// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Labscape/Components/ScoreComponent.h"
#include "Components/Statistic/StatisticComponent.h"
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
class LABSCAPE_API UBlueprintAssistFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Blueprint assist", meta = (WorldContext = "WorldContextObject"))
	static EBPNetMode GetNetMode(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Blueprint assist", meta = (WorldContext = "WorldContextObject"))
	static bool IsLocalPlayer(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Blueprint assist", meta = (WorldContext = "WorldContextObject"))
	static UUserWidget* GetParentUserWidget(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Blueprint assist")
	static UScoreComponent* GetScoreComponent(AActor* Target);

	UFUNCTION(BlueprintPure, Category = "Statistic")
	static UStatisticComponent* GetStatisticComponent(AActor* PlayerPawn);

	UFUNCTION(BlueprintPure, Category = "Statistic", meta = (DeterminesOutputType = "StatisticClass"))
	static UStatistic* GetStatistic(AActor* PlayerPawn, TSubclassOf<UStatistic> StatisticClass);
};
