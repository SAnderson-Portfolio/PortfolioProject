// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	

protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;

public:
	bool ShowMenu();
	bool RemoveMenu();
};
