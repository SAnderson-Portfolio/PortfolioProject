// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon_Melee.h"

#include "Entity_CharacterBase.h"

#include "InfantryCharacter.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;

UCLASS()
class PORTFOLIOPROJECT_API AInfantryCharacter : public AEntity_CharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AInfantryCharacter();

	UPROPERTY(EditAnywhere)
		UTexture2D* TempTexture;

	UFUNCTION(BlueprintCallable)
		bool GetIsMoving();

	UFUNCTION(BlueprintCallable)
		bool GetIsRunning();

	UFUNCTION(BlueprintCallable)
		bool GetIsInCombat();

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking();

	UFUNCTION(BlueprintCallable)
		void EndAttack();

	UFUNCTION(BlueprintCallable)
		void PerformAttack();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles stafing movement, left and right */
	void MoveRight(float Value);

	/* Handle Running*/
	void StartRun();
	void EndRun();

	//Handle Attacking
	void StartAttack();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* HeadMesh;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere)
		AWeapon_Melee* Weapon_L;

	UPROPERTY(VisibleAnywhere)
		AWeapon_Melee* Weapon_R;

	
private:
	bool bIsMoving;
	bool bIsRunning;
	bool bIsAttacking;
	bool bIsInCombat;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeapon_Melee> MeleeWeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
		UWidgetComponent* InventoryWidget;

	
};
