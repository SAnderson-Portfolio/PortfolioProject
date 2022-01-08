// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityStatComponent.h"
#include <limits>
// Sets default values for this component's properties
UEntityStatComponent::UEntityStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEntityStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEntityStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UEntityStatComponent::GetValue()
{
	if(!IsStatModified())
		return StatValue;

	float totalValue = StatValue;
	for (auto& value : StatModifiers)
	{

		totalValue += (StatValue / value.Value);
	}

	totalValue = FMath::Clamp(totalValue, 0.0f, std::numeric_limits<float>::max());
	return totalValue;
}

void UEntityStatComponent::SetValue(float newValue)
{
	StatValue = newValue;
}

bool UEntityStatComponent::IsStatModified()
{
	return (StatModifiers.Num() == 0);
}

void UEntityStatComponent::AddModifier(FString modifierName, float modifierValue)
{
	StatModifiers.Add(modifierName, modifierValue);
}

void UEntityStatComponent::RemoveModifier(FString modifierName)
{
	StatModifiers.Remove(modifierName);
}

void UEntityStatComponent::SubtractFromStat(float subtractValue)
{
	StatValue -= subtractValue;
}

void UEntityStatComponent::AddToStat(float addValue)
{
}

inline float& UEntityStatComponent::operator-=(const float& value)
{
	StatValue -= value;
	return StatValue;
}

inline float& UEntityStatComponent::operator+=(const float& value)
{
	StatValue += value;
	return StatValue;
}

