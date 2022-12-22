// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Chunk.generated.h"


USTRUCT(BlueprintType)
struct FNextChunkData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AChunk> ChunkClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ChanceOfSpawn = 1.0f;
};

UCLASS(Abstract)
class LABSCAPE_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UFUNCTION(BlueprintPure, Category = "Chunk")
	FVector GetChunkSize() const;
	
	UFUNCTION(BlueprintPure, Category = "Chunk")
	TSubclassOf<AChunk> GetNextChunk() const;
	
protected:

	UPROPERTY(EditDefaultsOnly)
	FVector ChunkSize;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ChunksData;
};
