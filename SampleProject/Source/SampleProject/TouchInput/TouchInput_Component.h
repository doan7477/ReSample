// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TouchInput_Interface.h"
#include "Components/ActorComponent.h"
#include "TouchInput_Component.generated.h"

//Event Dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputTouchAxisMoveForward, float, AxisValue, float, JoysticAngle, float, JoysticMoveLength);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputTouchAxisMoveRight, float, AxisValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLEPROJECT_API UTouchInput_Component : public UActorComponent, public ITouchInput_Interface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTouchInput_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Binding
	void Bind_TouchInputEvent();
	void EventInputTouchAxisMoveForward(float AxisValue, float JoysticAngle, float JoysticMoveLength);
	void EventInputTouchAxisMoveRight(float AxisValue);

public:
	UPROPERTY(BlueprintAssignable, Category = "InputTouch")
		FInputTouchAxisMoveForward InputTouchAxisMoveForward;
	UPROPERTY(BlueprintAssignable, Category = "InputTouch")
		FInputTouchAxisMoveRight InputTouchAxisMoveRight;

	//Touch Input Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnPressed_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnPressed_InputTouch_Implementation(FVector Location, uint8 FingerIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnReleased_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnReleased_InputTouch_Implementation(FVector Location, uint8 FingerIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Touch Input")
		void OnMoved_InputTouch(FVector Location, uint8 FingerIndex);
		virtual void OnMoved_InputTouch_Implementation(FVector Location, uint8 FingerIndex);
//Valueable
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<class UTouchInput_UserWidget> MainWidgetClass;
public:
	class UTouchInput_UserWidget* MainWidget;
};
