// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStruct.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	Knife,
	Handgun,
	Infantry,
	Machinegun,
	RocketLauncher
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None = 0,
	Weapon,
	Health,
	Shield
};