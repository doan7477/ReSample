// Fill out your copyright notice in the Description page of Project Settings.


#include "DWeapon.h"
#include "Animation/AnimMontage.h"
#include "Components/StaticMeshComponent.h"
#include "../Characters/DCharacter_Base.h"

// Sets default values
ADWeapon::ADWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//Attach
	RootComponent = Mesh;
	//Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void ADWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (WeaponData.WeaponID != 0)
	{

	}
}

// Called every frame
void ADWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADWeapon::AttackEvent_Implementation()
{
}

void ADWeapon::FireProjectile_Implementation()
{
}

void ADWeapon::SetPlayer(ADCharacter_Base* character)
{
	if (character == nullptr) return;
	PlayerRef = character;
}

