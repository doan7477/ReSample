// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchInput_Interface.h"

// Add default functionality here for any ITouchInput_Interface functions that are not pure virtual.

void ITouchInput_Interface::OnPressed_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
}

void ITouchInput_Interface::OnReleased_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
}

void ITouchInput_Interface::OnMoved_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
}

void ITouchInput_Interface::OnWidgetPressed_InputTouch_Implementation(UWidget* WidgetRef, FVector2D Position)
{
}

void ITouchInput_Interface::OnWidgetReleased_InputTouch_Implementation(UWidget* WidgetRef, FVector2D Position)
{
}

void ITouchInput_Interface::OnWidgetMoved_InputTouch_Implementation(UWidget* WidgetRef, FVector2D Position)
{
}
