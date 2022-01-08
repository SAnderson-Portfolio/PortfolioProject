// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickupObject.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityInventoryComponent.generated.h"

#define VALID_INVENTORY_SLOT(i, inventory) (inventory.IsValidIndex(i) && inventory[i] != NULL)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIOPROJECT_API UEntityInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntityInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		bool AddItemToInventory(APickupObject* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void UseItemAtSlot(int32 slot);

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		UTexture2D* GetThumbnailAtInventorySlot(int32 slot);

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		FString GetItemNameAtInventorySlot(int32 slot) const;

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		int32 GetItemValueAtInventorySlot(int32 slot) const;

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		int GetCurrentInventorySize() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void SetCurrentInventorySize(int32 newSize);

	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		APickupObject* GetItemAtSlot(int32 slot);


private:
	UPROPERTY()
	TArray<APickupObject*> Inventory;
		
};
