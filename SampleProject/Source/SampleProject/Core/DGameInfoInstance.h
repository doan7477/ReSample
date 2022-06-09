// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DGameInfoInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API UDGameInfoInstance : public UGameInstance
{
	GENERATED_BODY()

//Function
		UDGameInfoInstance();
public:
	UFUNCTION(BlueprintCallable)
		void SaveGameCheck();
	//Show Widget Menu
	UFUNCTION()
		void ShowMainMenu();
	UFUNCTION()
		void ShowHostMenu();
	UFUNCTION()
		void ShowServerMenu();
	UFUNCTION()
		void ShowOptionsMenu();
//Valiable
public:
	UPROPERTY()
		FString PlayerSettingSave;
	UPROPERTY()
		bool bCreateSaveFile;
	UPROPERTY()
		int MaxPlayers;
	UPROPERTY()
		FText ServerName;
	//Widget
	TSubclassOf<class UUserWidget> WidgetClass;
	UPROPERTY()
		class UUserWidget* MainMenu;
};
