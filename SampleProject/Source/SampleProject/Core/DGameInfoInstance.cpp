// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameInfoInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

UDGameInfoInstance::UDGameInfoInstance()
{
	PlayerSettingSave = TEXT("PlayerSettingsSave");

	static ConstructorHelpers::FObjectFinder<UClass>MAINMENU(TEXT("/Game/Sample/UI/Widget/WidgetBP_MainMenu_D.WidgetBP_MainMenu_D_C"));
	if (MAINMENU.Succeeded())
	{
		WidgetClass = MAINMENU.Object;
	}
}

void UDGameInfoInstance::SaveGameCheck()
{
	bool isSave = UGameplayStatics::DoesSaveGameExist(PlayerSettingSave, 0);
	UE_LOG(LogTemp, Warning, TEXT("SaveGameCheck!!"));
	if (isSave)
	{
		ShowMainMenu();
		bCreateSaveFile = true;
	}
	else
	{
		ShowOptionsMenu();
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->SetShowMouseCursor(true);
	}

}

//Show Widget UI Menu
void UDGameInfoInstance::ShowMainMenu()
{
	if (MainMenu == nullptr)
	{
		MainMenu = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	}
	MainMenu->AddToViewport(0);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetShowMouseCursor(true);
}

void UDGameInfoInstance::ShowHostMenu()
{
}

void UDGameInfoInstance::ShowServerMenu()
{
}

void UDGameInfoInstance::ShowOptionsMenu()
{
}
