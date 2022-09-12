// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FallingDown/Chunks/Chunk.h"
#include "GameFramework/Actor.h"
#include "ChunkGenerator.generated.h"

UCLASS(Blueprintable, Abstract, HideDropdown)
class FALLINGDOWN_API AChunkGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkGenerator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Chunks generator")
	int32 InitialChunksCount = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Chunks generator")
	UDataTable* ChunksDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Chunks generator")
	float ChunkUpdatePeriod = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = "Chunks generator")
	TSubclassOf<AChunk> DefaultChunksClass;

	UPROPERTY(EditDefaultsOnly, Category = "Chunks generator")
	int32 ChunksGenerationCount = 50;

private:

	void GenerateInitialChunks();

	void SpawnChunk(TSubclassOf<AChunk> Chunk);

	void UpdatePlayerPawnsList();

	void DestroyLastChunk();

	void DynamicChunkGeneration();

	FVector LastChunkPosition;

	TArray<AChunk*> Chunks;

	TArray<APawn*> PlayerPawns;

	
};
