// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "PickupObject.generated.h"

//UENUM()
//enum FPickupType
//{
//	Consumable,
//	Buff,
//
//}
/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API APickupObject : public AInteractableObject
{
	GENERATED_BODY()
public:
	APickupObject();

	virtual void BeginPlay() override;
	void InteractImplementation() override;
	virtual void UseImplementation();
	virtual void UseImplementation(FVector location);

	//Called when the item is picked up
	void OnPickUp();
	//Returns value of the item
	const int32& GetValue() const;
	//Sets the value of the item
	void SetValue(int32 newValue);
	//Returns the ItemName
	const FString& GetItemName() const;
	//Sets the ItemName
	void SetItemName(FString newName);
	//Returns the ItemThumbnail
	UTexture2D* GetThumbnail();
	//Sets the PickupThumbnail
	void SetThumbnail(UTexture2D* newThumbnail);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup Properties")
		UTexture2D* PickupThumbnail;

	UPROPERTY(VisibleAnywhere, Category = "Pickup Properties")
		FString ItemName;

	UPROPERTY(VisibleAnywhere, Category = "Pickup Properties")
		int32 Value;
};
