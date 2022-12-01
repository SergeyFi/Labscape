// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FallingDown/Components/ScoreComponent.h"
#include "FallingDown/Components/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerBase.generated.h"

UCLASS()
class FALLINGDOWN_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UScoreComponent* ScoreComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerBase")
	float PlayerMovementScoreScale = 0.001f;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerBase|Sounds")
	USoundBase* SoundDamage;

private:

	void AddScoreForMovement(float DeltaTime);

	UFUNCTION()
	void OnHealthCountChanged(int32 Count);
};
