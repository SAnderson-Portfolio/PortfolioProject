// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class UProgressBar* GetHealthBar() {
		return HealthBar;
	};

	

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	
};
