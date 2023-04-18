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

UStatistic* UStatisticComponent::GetStatistic(TSubclassOf<UStatistic> StatisticClass,  const EStatisticType Type)
{
	auto StatisticMap = StatisticsCurrent;

	if (Type == EStatisticType::Preview)
	{
		StatisticMap = StatisticsLast;
	}
	else if (Type == EStatisticType::Best)
	{
		StatisticMap = StatisticsBest;
	}
	
	if (StatisticClass)
	{
		auto StatisticFind = StatisticMap.Find(StatisticClass);

		if (StatisticFind)
		{
			return *StatisticFind;
		}
	}

	return nullptr;
}

TArray<UStatistic*> UStatisticComponent::GetStatistics(const EStatisticType Type)
{
	TArray<UStatistic*> Statistics;
	
	if (Type == EStatisticType::Current)
	{
		StatisticsCurrent.GenerateValueArray(Statistics);
	}
	else if (Type == EStatisticType::Best)
	{
		StatisticsBest.GenerateValueArray(Statistics);
	}
	else if (Type == EStatisticType::Preview)
	{
		StatisticsLast.GenerateValueArray(Statistics);
	}

	return Statistics;
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

float UStatisticComponent::GetScore(const EStatisticType Type)
{
	if (Type == EStatisticType::Current)
	{
		return GetScore(StatisticsCurrent);
	}
	else if (Type == EStatisticType::Best)
	{
		return GetScore(StatisticsBest);
	}
	else if (Type == EStatisticType::Preview)
	{
		return GetScore(StatisticsLast);
	}
	
	return 0.0f;
}

void UStatisticComponent::BeginPlay()
{
	Super::BeginPlay();

	InitStatisticObjects();

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
			Ar.ArIsSaveGame = true;

			auto StatisticObject = NewObject<UStatistic>(GetOwner(), StatData.StatClass);
			StatisticObject->Serialize(Ar);

			Statistic.Add(StatData.StatClass, StatisticObject);
		}
	}
}

void UStatisticComponent::SaveStatistics(const FString& SlotName, const TMap<TSubclassOf<UStatistic>, UStatistic*>& Statistic)
{
	if (!SlotName.IsEmpty())
	{
		auto StatSaveGame = Cast<UStatisticSaveGame>
		(UGameplayStatics::CreateSaveGameObject(UStatisticSaveGame::StaticClass()));
			
		for (auto& StatPair : Statistic)
		{
			FStatisticSaveData StatisticData;
			StatisticData.StatClass = StatPair.Value->GetClass();
		
			FMemoryWriter MemWriter(StatisticData.ByteData);
		
			FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
			Ar.ArIsSaveGame = true;
		
			StatPair.Value->Serialize(Ar);

			StatSaveGame->Statistics.Add(StatisticData);
			
		}

		UGameplayStatics::SaveGameToSlot(StatSaveGame, SlotName, 0);
	}
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

void UStatisticComponent::InitStatisticObjects()
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if(It->IsChildOf(UStatistic::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			auto NewStatistic = NewObject<UStatistic>(GetOwner(), *It);
			StatisticsCurrent.Add(*It, NewStatistic);

			NewStatistic = NewObject<UStatistic>(GetOwner(), *It);
			StatisticsLast.Add(*It, NewStatistic);

			NewStatistic = NewObject<UStatistic>(GetOwner(), *It);
			StatisticsBest.Add(*It, NewStatistic);
		}
	}
}
