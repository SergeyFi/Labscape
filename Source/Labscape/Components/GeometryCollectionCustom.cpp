// Fill out your copyright notice in the Description page of Project Settings.


#include "Labscape/Components/GeometryCollectionCustom.h"
#include "Components/ChildActorComponent.h"
#include "Field/FieldSystemActor.h"

void UGeometryCollectionCustom::NotifyPhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo)
{
	Super::NotifyPhysicsCollision(CollisionInfo);
}

void UGeometryCollectionCustom::OnCreatePhysicsState()
{
	AddPhysicsFieldsActors();
	
	Super::OnCreatePhysicsState();
}

void UGeometryCollectionCustom::AddPhysicsFieldsActors()
{
	TArray<UChildActorComponent*> ChildACtorComponents;
	GetOwner()->GetComponents<UChildActorComponent>(ChildACtorComponents);
	
	for (auto& Comp : ChildACtorComponents)
	{
		auto Field = Cast<AFieldSystemActor>(Comp->GetChildActor());
		
		if (Field)
		{
			InitializationFields.Add(Field);
		}
	}
}
