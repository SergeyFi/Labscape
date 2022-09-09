// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Chunks/Generators/ChunkGenerator.h"

// Sets default values
AChunkGenerator::AChunkGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChunkGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GenerateInitialChunks();
	}
}

void AChunkGenerator::GenerateInitialChunks()
{
	int32 CurrentChunkCount = 0;
	
	for (const auto& RowName : ChunksDataTable->GetRowNames())
	{
		FString ContextString;
			
		auto CurrentRow = ChunksDataTable->FindRow<FChunkDataRow>(RowName, ContextString);

		for (auto i = 0; i < CurrentRow->ChunkCount; ++i)
		{
			SpawnChunk(CurrentRow->ChunkClass);
			++CurrentChunkCount;

			if (CurrentChunkCount >= InitialChunksCount)
			{
				break;
			}
		}

		if (CurrentChunkCount >= InitialChunksCount)
		{
			break;
		}
	}
}

void AChunkGenerator::SpawnChunk(TSubclassOf<AChunk> Chunk)
{
	auto NewChunk = GetWorld()->SpawnActor<AChunk>(Chunk, LastChunkPosition, {});

	LastChunkPosition = NewChunk->GetActorLocation() - NewChunk->GetChunkSize();
}

// Called every frame
void AChunkGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
