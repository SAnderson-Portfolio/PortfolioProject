// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API AEnemyAIController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AEnemyAIController();
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;


private:
	//UPROPERTY(EditAnywhere)
	//	TSubclassOf<UUserWidget> HealthWidgetClass;

	//UPROPERTY(VisibleAnywhere)
	//	UUserWidget* HealthBar;

};
