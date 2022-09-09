// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

USTRUCT()
struct FChunkDataRow: public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AChunk> ChunkClass;

	UPROPERTY(EditAnywhere)
	int32 ChunkCount = 1;
};

UCLASS()
class FALLINGDOWN_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UFUNCTION(BlueprintPure, Category = "Chunk")
	FVector GetChunkSize() const;

protected:

	UPROPERTY(EditDefaultsOnly)
	FVector ChunkSize;
};
