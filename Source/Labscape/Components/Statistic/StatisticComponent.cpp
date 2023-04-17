// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Statistic/StatisticComponent.h"
#include "Components/Statistic/StatisticSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

// Sets default values for this component's properties
UStatisticComponent::UStatisticComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UStatistic* UStatisticComponent::GetStatistic(TSubclassOf<UStatistic> StatisticClass)
{
	if (StatisticClass)
	{
		auto StatisticFind = StatisticsCurrent.Find(StatisticClass);

		if (StatisticFind)
		{
			return *StatisticFind;
		}
		else
		{
			auto NewStatistic = NewObject<UStatistic>(GetOwner(),StatisticClass);
			StatisticsCurrent.Add(StatisticClass, NewStatistic);

			return NewStatistic;
		}
	}

	return nullptr;
}

void UStatisticComponent::SaveStatistic()
{
	if (IsSaveExist(StatisticBestSlot))
	{
		if (GetScore(StatisticsCurrent) > GetScore(StatisticsBest))
		{
			SaveStatistics(StatisticBestSlot, StatisticsCurrent);
		}

		SaveStatistics(StatisticLastSlot, StatisticsCurrent);
	}
	else
	{
		SaveStatistics(StatisticBestSlot, StatisticsCurrent);
		SaveStatistics(StatisticLastSlot, StatisticsCurrent);
	}
}

void UStatisticComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadStatistics(StatisticBestSlot, StatisticsBest);
	LoadStatistics(StatisticLastSlot, StatisticsLast);
}

void UStatisticComponent::LoadStatistics(const FString& SlotName, TMap<TSubclassOf<UStatistic>, UStatistic*>& Statistic)
{
	if (IsSaveExist(SlotName))
	{
		auto StatSaveGame = Cast<UStatisticSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			
		for (auto& StatData : StatSaveGame->Statistics)
		{
			FMemoryReader MemReader(StatData.ByteData);

			FObjectAndNameAsStringProxyArchive Ar(MemReader, true);

			auto StatisticObject = NewObject<UStatistic>(GetOwner(), StatData.StatClass);
			StatisticObject->Serialize(Ar);

			Statistic.Add(StatData.StatClass, StatisticObject);
		}
	}
}

void UStatisticComponent::SaveStatistics(const FString& SlotName, const TMap<TSubclassOf<UStatistic>, UStatistic*>& Statistic)
{
	auto StatSaveGame = Cast<UStatisticSaveGame>
	(UGameplayStatics::CreateSaveGameObject(UStatisticSaveGame::StaticClass()));
			
	for (auto& StatPair : Statistic)
	{
		FStatisticSaveData StatisticData;
		StatisticData.StatClass = StatPair.Value->StaticClass();
		
		FMemoryWriter MemWriter(StatisticData.ByteData);
		
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		
		StatPair.Value->Serialize(Ar);

		StatSaveGame->Statistics.Add(StatisticData);
	}

	UGameplayStatics::SaveGameToSlot(StatSaveGame, SlotName, 0);
}

float UStatisticComponent::GetScore(const TMap<TSubclassOf<UStatistic>,UStatistic*>& Statistic) const
{
	float Score = 0.0f;
	
	for (auto& Stat : Statistic)
	{
		Score += Stat.Value->GetScore();
	}

	return Score;
}

bool UStatisticComponent::IsSaveExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName,0);
}
