// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PortfolioProjectHUD.generated.h"

UCLASS()
class APortfolioProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	APortfolioProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

