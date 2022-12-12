// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Chunks/Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

FVector AChunk::GetChunkSize() const
{
	return ChunkSize;
}

TSubclassOf<AChunk> AChunk::GetNextChunk() const
{
	if (ChunksData)
	{
		TArray<FNextChunkData*> ChunksDatas;
		FString Message;
	
		ChunksData->GetAllRows<FNextChunkData>(Message, ChunksDatas);

		auto Probability = FMath::RandRange(0.0f, 1.0f);
		TArray<TPair<float, TSubclassOf<AChunk>>> ChunkSpawnPobability;
		ChunkSpawnPobability.Reserve(ChunksDatas.Num());
		int32 ChancesSum = 0;

		int32 LastIndex = ChunksDatas.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				ChunksDatas.Swap(i, Index);
			}
		}
	
		for (auto& Data : ChunksDatas)
		{
			if (Data->ChunkClass != GetClass())
			{
				ChancesSum += Data->ChanceOfSpawn;
			}
		}

		for (auto& Data : ChunksDatas)
		{
			if (Data->ChunkClass != GetClass())
			{
				ChunkSpawnPobability.Add({Data->ChanceOfSpawn / ChancesSum, Data->ChunkClass});
			}
		}

		for (auto& ChunkProbability : ChunkSpawnPobability)
		{
			if (ChunkProbability.Key <= Probability)
			{
				return ChunkProbability.Value;
			}
		}
	}

	return nullptr;
}
