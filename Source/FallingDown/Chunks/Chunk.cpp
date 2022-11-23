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

const TArray<TSubclassOf<AChunk>>& AChunk::GetNextChunks()
{
	return  NextChunksClasses;
}
