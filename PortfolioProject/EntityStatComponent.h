// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EntityStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIOPROJECT_API UEntityStatComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntityStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		float GetValue();

	UFUNCTION()
		void SetValue(float newValue);

	UFUNCTION()
		bool IsStatModified();

	UFUNCTION()
		void AddModifier(FString modifierName, float modifierValue);
	UFUNCTION()
		void RemoveModifier(FString modifierName);

	UFUNCTION()
		void SubtractFromStat(float subtractValue);
	UFUNCTION()
		void AddToStat(float addValue);

	inline float& operator-=(const float& value);
	inline float& operator+=(const float& value);
private:
	UPROPERTY()
		float StatValue;
	UPROPERTY()
		TMap<FString, float> StatModifiers;
};
