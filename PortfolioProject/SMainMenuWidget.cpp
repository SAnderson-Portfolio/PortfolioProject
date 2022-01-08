// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"
#include "Entity_CharacterBase.h"
#include "InventoryButton.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(50.0f, 100.0f);
	const FMargin ButtonPadding = FMargin(50.0f);
	const FMargin gridPadding = FMargin(10.0f, 10.0f);

	const FText TitleText = LOCTEXT("GameTitle", "Inventory");
	const FText PlayText = LOCTEXT("PlayGame", "Play");
	const FText SettingsText = LOCTEXT("Settings", "Settings");
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.0f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.0f;

	FSlateBrush topBarBrush;
	topBarBrush.SetImageSize(FVector2D(32.0f, 1000.0f));
	topBarBrush.DrawAs = ESlateBrushDrawType::Image;
	topBarBrush.Tiling = ESlateBrushTileType::NoTile;

	TSharedPtr<SUniformGridPanel> Container = SNew(SUniformGridPanel)
		.SlotPadding(gridPadding)
		.MinDesiredSlotHeight(120.0f)
		.MinDesiredSlotWidth(120.0f);

	int row = 0;
	int col = 0;
	int invSize = 0;
	if (OwningHUD.IsValid())
	{
		if (AEntity_CharacterBase* Entity = Cast<AEntity_CharacterBase>(OwningHUD->PlayerOwner->GetPawn()))
		{
			UEntityInventoryComponent* entityInventory = Entity->GetInventoryComponent();
			if (entityInventory != nullptr)
			{
				invSize = entityInventory->GetCurrentInventorySize();

				UE_LOG(LogTemp, Warning, TEXT("Owning HUD has Inventory"));
				for (int32 idx = 0; idx < invSize; idx++)
				{
					Container->AddSlot(col, row)
						[
							SNew(InventoryButton)
							.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
							.MyPickup(entityInventory->GetItemAtSlot(idx))
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(PlayText)
							.Justification(ETextJustify::Center)
						]
						];
					col++;
					if (col >= 5)
					{
						row++;
						col = 0;
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Inventory Component Found"));
			}
			
		}
	}
	
	ChildSlot
		[
			//Create an overlay for background image.
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[//Create the background image and set the colour.
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
				.RenderOpacity(0.65f)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
				.RenderOpacity(1.0f)
				.Image(&topBarBrush)
			]
			+SOverlay::Slot()//Add a slot for the title.
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.Padding(ContentPadding)
			[

				SNew(SVerticalBox)
				//Title Text
				+SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(TitleText)
					.Justification(ETextJustify::Center)
				]
			+SVerticalBox::Slot()
				[
					Container.ToSharedRef()
				]

				////Play Button
				//+SVerticalBox::Slot()
				//.Padding(ButtonPadding)
				//[
				//	SNew(SButton)
				//	.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
				//	[
				//		SNew(STextBlock)
				//		.Font(ButtonTextStyle)
				//		.Text(PlayText)
				//		.Justification(ETextJustify::Center)
				//	]
				//]

				
			]

			/*+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(ContentPadding)
			[
				Container.ToSharedRef()
			]*/
		];

	
}

void SMainMenuWidget::OnItemHover()
{

	UE_LOG(LogTemp, Warning, TEXT("Button Hover"));
}

FReply SMainMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu();
	}

	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("Play Clicked"));
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("Quit");
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE