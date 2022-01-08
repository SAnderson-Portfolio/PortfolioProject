// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityInventoryComponent.h"

// Sets default values for this component's properties
UEntityInventoryComponent::UEntityInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEntityInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEntityInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEntityInventoryComponent::AddItemToInventory(APickupObject* Item)
{
	if(Item == NULL)
		return false;

	const int32 AvailableSlot = Inventory.Find(NULL);

	if (AvailableSlot != INDEX_NONE)
	{
		Inventory[AvailableSlot] = Item;
		return true;
	}

	return false;
}

void UEntityInventoryComponent::UseItemAtSlot(int32 slot)
{
	if (VALID_INVENTORY_SLOT(slot, Inventory))
	{
		Inventory[slot]->UseImplementation();
		Inventory[slot] = NULL;
	}

	/*if (Inventory.IsValidIndex(slot))
	{
		if (Inventory[slot] != NULL)
		{
			Inventory[slot]->UseImplementation();
			Inventory[slot] = NULL;
		}
	}*/
}

UTexture2D* UEntityInventoryComponent::GetThumbnailAtInventorySlot(int32 slot) 
{
	if (VALID_INVENTORY_SLOT(slot, Inventory))
		return Inventory[slot]->GetThumbnail();

	/*if (Inventory.IsValidIndex(slot))
	{
		if(Inventory[slot] != NULL)
			return Inventory[slot]->GetThumbnail();
	}*/

	return nullptr;
}

FString UEntityInventoryComponent::GetItemNameAtInventorySlot(int32 slot) const
{
	if (VALID_INVENTORY_SLOT(slot, Inventory))
	{
		return Inventory[slot]->GetItemName();
	}

	/*if (Inventory.IsValidIndex(slot))
	{
		if (Inventory[slot] != NULL)
			return Inventory[slot]->GetItemName();
	}*/
	return FString("NONE");
}

int32 UEntityInventoryComponent::GetItemValueAtInventorySlot(int32 slot) const
{
	if (VALID_INVENTORY_SLOT(slot, Inventory))
	{
		return Inventory[slot]->GetValue();
	}
	/*if (Inventory.IsValidIndex(slot))
	{
		if (Inventory[slot] != NULL)
			return Inventory[slot]->GetValue();
	}*/

	return (int32)0;
}

int UEntityInventoryComponent::GetCurrentInventorySize() const
{
	
	return Inventory.Num();
}

void UEntityInventoryComponent::SetCurrentInventorySize(int32 newSize)
{
	Inventory.SetNum(newSize);
}

APickupObject* UEntityInventoryComponent::GetItemAtSlot(int32 slot)
{
	if (VALID_INVENTORY_SLOT(slot, Inventory))
	{
		return Inventory[slot];
	}
	/*if (Inventory.IsValidIndex(slot))
	{
		if (Inventory[slot] != NULL)
		{
			return Inventory[slot];
		}
	}*/

	return nullptr;
}

