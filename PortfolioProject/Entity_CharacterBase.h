// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EntityInventoryComponent.h"
#include "Entity_CharacterBase.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AEntity_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		inline UEntityInventoryComponent* GetInventoryComponent() {	return InventoryComponent;	};

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		UEntityInventoryComponent* InventoryComponent;

};
