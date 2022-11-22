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

// Called every frame
void AChunkGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		DynamicChunkGeneration();
	}
}

void AChunkGenerator::GenerateInitialChunks()
{
	if (InitialChunk && InitialChunksCount > 0)
	{
		auto LastChunk = SpawnChunk(InitialChunk);

		for (auto i = 0; i < InitialChunksCount - 1; ++i)
		{
			LastChunk = SpawnChunk(LastChunk->GetNextChunks()[FMath::RandRange(0, LastChunk->GetNextChunks().Num() - 1)]);
		}
	}
	else
	{
		SetActorTickEnabled(false);
	}
}

AChunk* AChunkGenerator::SpawnChunk(TSubclassOf<AChunk> Chunk)
{;
	auto NewChunk = GetWorld()->SpawnActor<AChunk>(Chunk, LastChunkPosition, UChunkFunctionLibrary::GetBlockRandomRotation());
	NewChunk->SetActorScale3D({ChunkScale, ChunkScale, ChunkScale});

	LastChunkPosition = NewChunk->GetActorLocation() - NewChunk->GetChunkSize();

	Chunks.Add(NewChunk);

	return NewChunk;
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
		
	if (PlayerPawns.Num() != 0 && Chunks.Num() >= 1)
	{
		if (PlayerPawns.Last()->GetActorLocation().Z + ChunkRemoveOffset < Chunks[0]->GetActorLocation().Z)
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
