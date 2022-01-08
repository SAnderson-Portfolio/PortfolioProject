// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entity_CharacterBase.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;
UCLASS()
class PORTFOLIOPROJECT_API AEnemyCharacter : public AEntity_CharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Enemy Information")
		float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void FinishHim();

	UPROPERTY(EditAnywhere, Category = "Debug")
		uint8 DebugInfo : 1;
private:
	float Health;
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
		UWidgetComponent* HealthBar;

	UPROPERTY(VisibleAnywhere, Category = "Meshes")
		USkeletalMeshComponent* HeadMesh;
};
