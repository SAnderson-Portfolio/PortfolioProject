// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioPlayerController.h"

#include "MenuHUD.h"

APortfolioPlayerController::APortfolioPlayerController()
{
	bInventoryOpen = false;
}

void APortfolioPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		FInputActionBinding& toggle = InputComponent->BindAction("OpenInventory", IE_Pressed, this, &APortfolioPlayerController::OpenMenu);
		toggle.bExecuteWhenPaused = true;
	}
}

void APortfolioPlayerController::OpenMenu()
{
	if (AMenuHUD* MenuHUD = Cast<AMenuHUD>(GetHUD()))
	{
		bool result = false;
		if (!bInventoryOpen)
		{
			result = MenuHUD->ShowMenu();

			UE_LOG(LogTemp, Warning, TEXT("Showing Inventory"));
			if (result)
				bInventoryOpen = true;
		}
		else
		{
			result = MenuHUD->RemoveMenu();

			UE_LOG(LogTemp, Warning, TEXT("Removing Inventory"));
			if (result)
				bInventoryOpen = false;
		}
	}
}