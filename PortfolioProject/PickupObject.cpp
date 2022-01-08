// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"

APickupObject::APickupObject()
{
	//Setup the mesh for the pickup and set the item name, help text and item value
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	InteractableMesh->SetSimulatePhysics(true);
	SetRootComponent(InteractableMesh);
	//PickupThumbnail = NULL;

	ItemName = FString("Enter an item name here...");

	InteractableHelpText = FString("Press E to pick item up");
	Value = 0;
}

void APickupObject::BeginPlay()
{
	Super::BeginPlay();
	InteractableHelpText = FString::Printf(TEXT("%s: Press E to pick up"), *ItemName);
}

void APickupObject::InteractImplementation()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractImplementation called from base class."));
}

void APickupObject::UseImplementation()
{
	UE_LOG(LogTemp, Warning, TEXT("UseImplementation called from base class."));
}

void APickupObject::UseImplementation(FVector location)
{
	UE_LOG(LogTemp, Warning, TEXT("UseImplementation(FVector) called from base class."));
}

void APickupObject::OnPickUp()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

const int32& APickupObject::GetValue() const
{
	return Value;
}

void APickupObject::SetValue(int32 newValue)
{
	Value = newValue;
}

const FString& APickupObject::GetItemName() const
{
	return ItemName;
}

void APickupObject::SetItemName(FString newName)
{
	ItemName = newName;
}

UTexture2D* APickupObject::GetThumbnail()
{
	return PickupThumbnail;
}

void APickupObject::SetThumbnail(UTexture2D* newThumbnail)
{
	PickupThumbnail = newThumbnail;
}
