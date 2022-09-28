// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingDown/Chunks/Generators/ChunkGenerator.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "FallingDown/Chunks/ChunkFunctionLibrary.h"

// Sets default values
AChunkGenerator::AChunkGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = ChunkUpdatePeriod;
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
{;
	auto NewChunk = GetWorld()->SpawnActor<AChunk>(Chunk, LastChunkPosition, UChunkFunctionLibrary::GetBlockRandomRotation());
	NewChunk->SetActorScale3D({ChunkScale, ChunkScale, ChunkScale});

	LastChunkPosition = NewChunk->GetActorLocation() - NewChunk->GetChunkSize();

	Chunks.Add(NewChunk);
}

void AChunkGenerator::UpdatePlayerPawnsList()
{
	auto PlayerStates = UGameplayStatics::GetGameState(GetWorld())->PlayerArray;

	PlayerPawns.Empty();
	
	for (auto& State : PlayerStates)
	{
		PlayerPawns.Add(State->GetPawn());
	}

	PlayerPawns.Sort([](const APawn& A, const APawn& B)
	{
		return A.GetActorLocation().Z < B.GetActorLocation().Z;
	});
}

void AChunkGenerator::DestroyLastChunk()
{
	Chunks[0]->Destroy();
	Chunks.RemoveAt(0);
}

void AChunkGenerator::DynamicChunkGeneration()
{
	UpdatePlayerPawnsList();
		
	if (PlayerPawns.Num() != 0 && Chunks.Num() != 0)
	{
		if (PlayerPawns.Last()->GetActorLocation().Z + 1000.0f < Chunks[0]->GetActorLocation().Z)
		{
			DestroyLastChunk();
		}
			
		if (PlayerPawns[0]->GetActorLocation().Z + -ChunkGenerationOffset < Chunks.Last()->GetActorLocation().Z)
		{
			for (auto i = 0; i < ChunksGenerationCount; ++i)
			{
				SpawnChunk(DefaultChunksClass);
			}
		}
	}
}

// Called every frame
void AChunkGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		DynamicChunkGeneration();
	}
}
