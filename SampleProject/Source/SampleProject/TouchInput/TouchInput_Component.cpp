// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchInput_Component.h"
#include "TouchInput_UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTouchInput_Component::UTouchInput_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UTouchInput_UserWidget>MAIN_UI(TEXT("/Game/Sample/UI/Widget/WidgetBP_BattleMain.WidgetBP_BattleMain_C"));
	if (MAIN_UI.Succeeded())
	{
		MainWidgetClass = MAIN_UI.Class;
	}
	// ...
}


// Called when the game starts
void UTouchInput_Component::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	auto PC = Cast<APlayerController>(Owner);
	if (PC != nullptr)
	{
		if (PC->IsLocalController())
		{
			MainWidget = CreateWidget<UTouchInput_UserWidget>(PC, MainWidgetClass);
			MainWidget->AddToViewport();
			Bind_TouchInputEvent();
		}
	}
	else
	{
		auto Pawn = Cast<APawn>(Owner);
		if (Pawn != nullptr)
		{
			if (Pawn->IsLocallyControlled())
			{
				auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				MainWidget = CreateWidget<UTouchInput_UserWidget>(pc, MainWidgetClass);
				MainWidget->AddToViewport();
				Bind_TouchInputEvent();
			}
		}
	}
	// ...
	
}


// Called every frame
void UTouchInput_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//Bind
void UTouchInput_Component::Bind_TouchInputEvent()
{
	//MainWidget->InputTouchAxisMoveForward.AddDynamic(this, &UTouchInput_Component::EventInputTouchAxisMoveForward);
	//MainWidget->InputTouchAxisMoveRight.AddDynamic(this, &UTouchInput_Component::EventInputTouchAxisMoveRight);
}
void UTouchInput_Component::EventInputTouchAxisMoveForward(float AxisValue, float JoysticAngle, float JoysticMoveLength)
{
	InputTouchAxisMoveForward.Broadcast(AxisValue, JoysticAngle, JoysticMoveLength);
}

void UTouchInput_Component::EventInputTouchAxisMoveRight(float AxisValue)
{
	InputTouchAxisMoveRight.Broadcast(AxisValue);
}

//Touch Input Interface
void UTouchInput_Component::OnPressed_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
	MainWidget->OnPressed_InputTouch_Implementation(Location, FingerIndex);
}

void UTouchInput_Component::OnReleased_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
	MainWidget->OnReleased_InputTouch_Implementation(Location, FingerIndex);
}

void UTouchInput_Component::OnMoved_InputTouch_Implementation(FVector Location, uint8 FingerIndex)
{
	MainWidget->OnMoved_InputTouch_Implementation(Location, FingerIndex);
}

