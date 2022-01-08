// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.h"

AEnemyAIController::AEnemyAIController()
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> HealthWidgetBaseClass(TEXT("WidgetBlueprint'/Game/UI/HealthBarBP.HealthBarBP_C'"));
	//if (HealthWidgetBaseClass.Class != NULL)
	//{
	//	HealthWidgetClass = HealthWidgetBaseClass.Class;
	//}
}
void AEnemyAIController::BeginPlay()
{
	/*HealthBar = CreateWidget(GetOwner(), HealthWidgetClass);
	if (HealthBar != nullptr)
	{
		HealthBar->AddToViewport();
		auto healthbarWidget = Cast<UHealthBarWidget>(HealthBar);
		if (healthbarWidget)
		{
			healthbarWidget->GetHealthBar()->PercentDelegate.BindUFunction(GetOwner(), FName("GetHealth"));
		}
	}*/
}

void AEnemyAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
}
