// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryButton.h"

InventoryButton::InventoryButton()
{

}

InventoryButton::~InventoryButton()
{

}

void InventoryButton::Construct(const FArguments& InArgs)
{
	SButton::Construct(SButton::FArguments()
		.ContentScale(InArgs._ContentScale)
		.DesiredSizeScale(InArgs._DesiredSizeScale)
		.ForegroundColor(InArgs._ForegroundColor)
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign));

	MyPickup = InArgs._MyPickup;

	if (MyPickup)
	{
		ButtonStyle = FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button");

		FSlateBrush buttonAppearance;
		buttonAppearance.SetResourceObject(MyPickup->GetThumbnail());

		ButtonStyle.SetNormal(buttonAppearance);
		ButtonStyle.SetHovered(buttonAppearance);
		//style.Normal.SetResourceObject(MyPickup->GetThumbnail());
		SetButtonStyle(&ButtonStyle);

	}
}

void InventoryButton::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	SButton::OnMouseEnter(MyGeometry, MouseEvent);
	SetRenderOpacity(0.5f);
}

void InventoryButton::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SButton::OnMouseLeave(MouseEvent);
	SetRenderOpacity(1.0f);
}

FReply InventoryButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MyPickup)
	{
		MyPickup->UseImplementation();
	}
	return FReply::Handled();
}

//void InventoryButton::InitButton(APickupObject* newPickup)
//{
//	if (newPickup == nullptr)
//		return;
//
//	//SetPickupObject(newPickup);
//	UTexture2D* tempTexture = MyPickup->GetThumbnail();
//
//	FSlateBrush buttonAppearance;
//	buttonAppearance.SetResourceObject(tempTexture);
//
//	FButtonStyle buttonStyle;
//	buttonStyle.SetNormal(buttonAppearance);
//	SetButtonStyle(&buttonStyle);
//}
