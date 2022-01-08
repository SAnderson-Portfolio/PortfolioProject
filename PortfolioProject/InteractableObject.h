// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractImplementation();

	//Returns the InteractableHelpText
	UFUNCTION(BlueprintCallable, Category = "Interactable Properties")
		const FString& GetInteractableText() const;
	//Sets the InteractableHelpText
	UFUNCTION(BlueprintCallable, Category = "Interactable Properties")
		void SetInteractableText(FString newText);

	//Returns the InteractableMesh
	UFUNCTION(BlueprintCallable, Category = "Interactable Properties")
		UStaticMeshComponent* GetInteractableMesh();
	//Sets the InteractableMesh
	UFUNCTION(BlueprintCallable, Category = "Interactable Properties")
		void SetInteractableMesh(UStaticMeshComponent* newMesh);

protected:
	UPROPERTY(EditAnywhere, Category = "Interactable Properties")
		class UStaticMeshComponent* InteractableMesh;

	UPROPERTY(EditAnywhere, Category = "Interactable Properties")
		FString InteractableHelpText;
};
