// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/Input/SButton.h"
#include "PickupObject.h"

#include "CoreMinimal.h"

/**
 * 
 */
class PORTFOLIOPROJECT_API InventoryButton : public SButton
{
public:
	

	SLATE_BEGIN_ARGS(InventoryButton)
		: _Content()
		, _MyPickup(nullptr)
		, _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button"))
		, _TextStyle(&FCoreStyle::Get().GetWidgetStyle< FTextBlockStyle >("NormalText"))
		, _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Fill)
		, _ContentPadding(FMargin(4.0, 2.0))
		, _Text()
		, _ClickMethod(EButtonClickMethod::DownAndUp)
		, _TouchMethod(EButtonTouchMethod::DownAndUp)
		, _PressMethod(EButtonPressMethod::DownAndUp)
		, _DesiredSizeScale(FVector2D(1, 1))
		, _ContentScale(FVector2D(1, 1))
		, _ButtonColorAndOpacity(FLinearColor::White)
		, _ForegroundColor(FCoreStyle::Get().GetSlateColor("InvertedForeground"))
		, _IsFocusable(true)
		
	{
	}

	/** Slot for this button's content (optional) */
	SLATE_DEFAULT_SLOT(FArguments, Content)

	/** The visual style of the button */
	SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)

	/** The text style of the button */
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)

	/** Horizontal alignment */
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

	/** Vertical alignment */
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	

	/** Spacing between button's border and the content. */
	SLATE_ATTRIBUTE(FMargin, ContentPadding)


	/** The text to display in this button, if no custom content is specified */
	SLATE_ATTRIBUTE(FText, Text)

	/** Called when the button is clicked */
	SLATE_EVENT(FOnClicked, OnClicked)

	/** Called when the button is pressed */
	SLATE_EVENT(FSimpleDelegate, OnPressed)

	/** Called when the button is released */
	SLATE_EVENT(FSimpleDelegate, OnReleased)

	SLATE_EVENT(FSimpleDelegate, OnHovered)

	SLATE_EVENT(FSimpleDelegate, OnUnhovered)

	/** Sets the rules to use for determining whether the button was clicked.  This is an advanced setting and generally should be left as the default. */
	SLATE_ARGUMENT(EButtonClickMethod::Type, ClickMethod)

	/** How should the button be clicked with touch events? */
	SLATE_ARGUMENT(EButtonTouchMethod::Type, TouchMethod)

	/** How should the button be clicked with keyboard/controller button events? */
	SLATE_ARGUMENT(EButtonPressMethod::Type, PressMethod)

	SLATE_ATTRIBUTE(FVector2D, DesiredSizeScale)

	SLATE_ATTRIBUTE(FVector2D, ContentScale)

	SLATE_ATTRIBUTE(FSlateColor, ButtonColorAndOpacity)

	SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)

	/** Sometimes a button should only be mouse-clickable and never keyboard focusable. */
	SLATE_ARGUMENT(bool, IsFocusable)

	/** The sound to play when the button is pressed */
	SLATE_ARGUMENT(TOptional<FSlateSound>, PressedSoundOverride)

	/** The sound to play when the button is hovered */
	SLATE_ARGUMENT(TOptional<FSlateSound>, HoveredSoundOverride)

	/** Which text shaping method should we use? (unset to use the default returned by GetDefaultTextShapingMethod) */
	SLATE_ARGUMENT(TOptional<ETextShapingMethod>, TextShapingMethod)

	/** Which text flow direction should we use? (unset to use the default returned by GetDefaultTextFlowDirection) */
	SLATE_ARGUMENT(TOptional<ETextFlowDirection>, TextFlowDirection)

	/*The PickupObject that this button owns*/
	SLATE_ARGUMENT(APickupObject*, MyPickup)

	SLATE_END_ARGS()

	InventoryButton();
	~InventoryButton();
	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);

	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	/*void SetPickupObject(APickupObject* newPickup);
	APickupObject* GetPickupObject();*/

	//void InitButton(APickupObject* newPickup);

	
private:
	UPROPERTY(VisibleAnywhere)
		APickupObject* MyPickup;

	UPROPERTY()
		FButtonStyle ButtonStyle;
};
