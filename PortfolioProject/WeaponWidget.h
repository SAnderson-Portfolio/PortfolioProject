// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE class UTextBlock* GetWeaponNameBlock() {
		return WeaponName;
	};

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* WeaponName;
};
