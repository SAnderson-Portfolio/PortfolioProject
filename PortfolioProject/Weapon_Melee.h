// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickupObject.h"


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Melee.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;

USTRUCT()
struct FWeaponTiers
{
	GENERATED_BODY()

public:
	FWeaponTiers()
	{
		DamageIncrease = 0;
		RangeIncrease = 0;
	}

	FWeaponTiers(float a, float b)
	{
		DamageIncrease = a;
		RangeIncrease = b;
	}

	float DamageIncrease;
	float RangeIncrease;
};

UCLASS()
class PORTFOLIOPROJECT_API AWeapon_Melee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Melee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PerformAttack();

	float GetWeaponDamage();

	UFUNCTION(BlueprintPure, Category = "Weapon Info")
		FText GetWeaponName() const;

	void SetWidgetVisibility();
private:
	float WeaponBaseDamage;
	float PercentDamageIncrease;
	float AttackRadius;
	FText WeaponName;
	FWeaponTiers CurrentWeaponTier;
	int32 CurrentTier;
	UPROPERTY(VisibleAnywhere, Category = "Weapon Info")
		class UWidgetComponent* WeaponWidget;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Info")
		class UStaticMeshComponent* InteractableMesh;

	const FWeaponTiers WeaponTiers[2] = { {120.0f, 100.0f}, {150.0f, 10.0f} };
};
