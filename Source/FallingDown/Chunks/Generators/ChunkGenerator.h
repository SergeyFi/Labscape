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

private:

	void GenerateInitialChunks();

	void SpawnChunk(TSubclassOf<AChunk> Chunk);

	FVector LastChunkPosition;
};
