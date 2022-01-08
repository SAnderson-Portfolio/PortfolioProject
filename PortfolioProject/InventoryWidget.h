// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UButton;
/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	inline class UUniformGridPanel* GetInventoryPanel() {
		return InventoryPanel;
	};

	inline TArray<UButton*>& GetInventoryItems()
	{
		return InventoryItems;
	}

private:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* InventoryPanel;

	UPROPERTY(meta = (BindWidget))
		TArray<UButton*> InventoryItems;
};
