// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

UCLASS()
class LABSCAPE_API APickable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Pickable")
	float GatheringSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Pickable")
	float GatherDistance = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Pickable")
	float GatheringTimeMax = 1.0f;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision;

	virtual void OnGather(AActor* PlayerTarget);

private:

	AActor* Target;

	float GatheringTime;

	UFUNCTION()
	void OnPickableOverlap(AActor* This, AActor* Other);

};
