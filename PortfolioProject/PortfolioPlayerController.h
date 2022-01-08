// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PortfolioPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API APortfolioPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	APortfolioPlayerController();

	virtual void SetupInputComponent() override;

	void OpenMenu();

	bool bInventoryOpen;
};
