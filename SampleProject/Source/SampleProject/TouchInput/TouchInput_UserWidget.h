// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TouchInput_Interface.h"
#include "Blueprint/UserWidget.h"
#include "TouchInput_UserWidget.generated.h"

//Event Dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FInputTouchAxisMoveForwardDelegate, float, AxisValue, float, JoysticAngle, float, JoysticMoveLength);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FInputTouchAxisMoveRightDelegate, float, AxisValue);
/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API UTouchInput_UserWidget : public UUserWidget, public ITouchInput_Interface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "InputTouch")
		FInputTouchAxisMoveForwardDelegate InputTouchAxisMoveForward;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "InputTouch")
		FInputTouchAxisMoveRightDelegate InputTouchAxisMoveRight;
};
