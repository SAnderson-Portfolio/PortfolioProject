// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"

#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
//#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	//ShowMenu();
	MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
}

bool AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
		if (PlayerOwner)
		{
			//PlayerOwner->bShowMouseCursor = true;
			//PlayerOwner->SetInputMode(FInputModeUIOnly());
			PlayerOwner->SetShowMouseCursor(true);
			PlayerOwner->Pause();
			return true;
		}
	}

	return false;
}

bool AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
		if (PlayerOwner)
		{
			//PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetShowMouseCursor(false);
			//PlayerOwner->SetInputMode(FInputModeGameOnly());
			PlayerOwner->Pause();
			return true;
		}
	}

	return false;
}