// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "UObject/Interface.h"
#include "TouchInput_Interface.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FWidgetTouchInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		class UWidget* Widget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		uint8 FingerIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		FVector PressedLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		FVector2D PressedLoc2D_WidgetSpace;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TouchInput")
		FVector2D Loc2D_WidgetSpace;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTouchInput_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMPLEPROJECT_API ITouchInput_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnPressed_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnPressed_InputTouch_Implementation(FVector Location, uint8 FingerIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnReleased_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnReleased_InputTouch_Implementation(FVector Location, uint8 FingerIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnMoved_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnMoved_InputTouch_Implementation(FVector Location, uint8 FingerIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnWidgetPressed_InputTouch(class UWidget* WidgetRef, FVector2D Position);
		virtual void OnWidgetPressed_InputTouch_Implementation(UWidget* WidgetRef, FVector2D Position);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnWidgetReleased_InputTouch(class UWidget* WidgetRef, FVector2D Position);
		virtual void OnWidgetReleased_InputTouch_Implementation(UWidget* WidgetRef, FVector2D Position);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnWidgetMoved_InputTouch(class UWidget* WidgetRef, FVector2D Position);
		virtual void OnWidgetMoved_InputTouch_Implementation(class UWidget* WidgetRef, FVector2D Position);
};
