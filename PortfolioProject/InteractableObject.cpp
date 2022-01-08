// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableHelpText = FString("Press E to interact with item.");
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::InteractImplementation()
{
	GLog->Log("Interact base class: InteractImplementation()");
}

const FString& AInteractableObject::GetInteractableText() const
{
	return InteractableHelpText;
}

void AInteractableObject::SetInteractableText(FString newText)
{
	InteractableHelpText = newText;
}

UStaticMeshComponent* AInteractableObject::GetInteractableMesh()
{
	return InteractableMesh;
}

void AInteractableObject::SetInteractableMesh(UStaticMeshComponent* newMesh)
{
	InteractableMesh = newMesh;
}

