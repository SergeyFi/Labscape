// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Chunks/Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = bRotating;
	bReplicates = true;
}

void AChunk::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	AddActorLocalRotation(RotationRate * DeltaTime);
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

		
		int32 LastIndex = ChunksDatas.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				ChunksDatas.Swap(i, Index);
			}
		}
		

		auto ChancesSum = 0.0f;
		auto MaxChance = 0.0f;
		for (auto& NextChunkData : ChunksDatas)
		{
			ChancesSum += NextChunkData->ChanceOfSpawn;

			if (NextChunkData->ChanceOfSpawn > MaxChance)
			{
				MaxChance = NextChunkData->ChanceOfSpawn;
			}
		}
		

		auto Probability = FMath::RandRange(0.0f, MaxChance / ChancesSum);

		for (auto& NextChunkData : ChunksDatas)
		{
			if (NextChunkData->ChanceOfSpawn / ChancesSum  >= Probability)
			{
				return NextChunkData->ChunkClass;
			}
		}

		return ChunksDatas[0]->ChunkClass;
	}

	return nullptr;
}

void AChunk::BeginPlay()
{
	Super::BeginPlay();

	bool RandBool = FMath::RandBool();

	if (RandBool)
	{
		RotationRate = {0.0f, FMath::RandRange(5.0f, 10.0f), 0.0f};
	}
	else
	{
		RotationRate = {0.0f, FMath::RandRange(-5.0f, -10.0f), 0.0f};
	}
}
