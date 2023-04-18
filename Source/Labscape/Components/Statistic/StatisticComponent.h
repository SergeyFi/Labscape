// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Statistic.h"
#include "StatisticComponent.generated.h"

UENUM(BlueprintType)
enum class EStatisticType : uint8
{
	Current		UMETA(DiplayName = "Current"),
	Preview		UMETA(DisplayName = "Preview"),
	Best		UMETA(DisplayName = "Best")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UStatisticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatisticComponent();

	UFUNCTION(BlueprintPure, Category = "Statistic", meta = (DeterminesOutputType = "StatisticClass"))
	UStatistic* GetStatistic(TSubclassOf<UStatistic> StatisticClass, const EStatisticType Type = EStatisticType::Current);

	UFUNCTION(BlueprintPure, Category = "Statistic")
	TArray<UStatistic*> GetStatistics(const EStatisticType Type);
	
	UFUNCTION(BlueprintCallable, Category = "Statistic")
	void SaveStatistic();

	UFUNCTION(BlueprintPure, Category = "Statistic")
	float GetScore(const EStatisticType Type = EStatisticType::Current);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<TSubclassOf<UStatistic>, UStatistic*> StatisticsCurrent;

	UPROPERTY()
	TMap<TSubclassOf<UStatistic>, UStatistic*> StatisticsBest;

	UPROPERTY()
	TMap<TSubclassOf<UStatistic>, UStatistic*> StatisticsLast;
	
	FString StatisticBestSlot = "statistic_best";

	FString StatisticLastSlot = "statistic_last";

	void LoadStatistics(const FString& SlotName, TMap<TSubclassOf<UStatistic>,UStatistic*>& Statistic);

	void SaveStatistics(const FString& SlotName, const TMap<TSubclassOf<UStatistic>,UStatistic*>& Statistic);

	float GetScore(const TMap<TSubclassOf<UStatistic>,UStatistic*>& Statistic) const;

	bool IsSaveExist(const FString& SlotName);

	void InitStatisticObjects();
};
