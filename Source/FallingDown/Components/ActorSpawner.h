// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ActorSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UActorSpawner : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	virtual void OnUnregister() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	float SpawnProbability = 1.0f;

private:

	UPROPERTY()
	AActor* ChildActor;

	void SpawnChild();
};
