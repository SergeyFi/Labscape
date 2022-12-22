// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSubcomponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthEvent, int32, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABSCAPE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddDamage(int32 Damage);

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	bool HealthIsOver();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Kill();
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEvent OnHealthCountChanged;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 Health;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Health")
	TArray<UHealthSubcomponent*> Subcomponents;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool bGodMode;

private:

	UFUNCTION(Client, Reliable)
	void UpdateHealthOnClient(int32 HealthCount);
};
