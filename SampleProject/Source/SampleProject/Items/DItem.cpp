// Fill out your copyright notice in the Description page of Project Settings.


#include "DItem.h"
#include "../Weapons/DWeapon.h"
#include "../Characters/DCharacter_Base.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADItem::ADItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	WeaponItemClass = ADWeapon::StaticClass();

	RootComponent = SphereCollision;
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BOX(TEXT("/Game/PolygonTown/Meshes/Props/SM_Prop_CardboardBox_01.SM_Prop_CardboardBox_01"));
	if (SM_BOX.Succeeded()) Mesh->SetStaticMesh(SM_BOX.Object);

	SphereCollision->SetSphereRadius(60.0f);

}

void ADItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADItem::OnCharacterOverlap);
}

void ADItem::OnCharacterOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	
	if (ItemType == EItemType::Weapon)
	{
		auto Character = Cast<ADCharacter_Base>(OtherActor);
		if (Character != nullptr && WeaponItemClass != nullptr)
		{
			if (Character->IsEquipWeapon() == false)
			{
				auto NewWeapon = GetWorld()->SpawnActor<ADWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
				Character->EquipWeapon(NewWeapon);
				this->Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Character already equip weapon!"));
			}
		}

	}
}



// Called when the game starts or when spawned
void ADItem::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ADItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

