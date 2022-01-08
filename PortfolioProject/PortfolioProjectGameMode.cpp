// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioProjectGameMode.h"
#include "PortfolioProjectHUD.h"
#include "PortfolioProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PortfolioPlayerController.h"
#include "MenuHUD.h"
APortfolioProjectGameMode::APortfolioProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = APortfolioProjectHUD::StaticClass();

	HUDClass = AMenuHUD::StaticClass();
	PlayerControllerClass = APortfolioPlayerController::StaticClass();
}
