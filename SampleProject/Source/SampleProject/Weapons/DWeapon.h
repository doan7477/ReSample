// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "GameFramework/Actor.h"
#include "../Core/CommonStruct.h"
#include "DWeapon.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Data)
	int32 WeaponID;
	UPROPERTY(EditAnywhere, Category = Data)
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
	class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, Category = Data)
	float Damage;
};

UCLASS()
class SAMPLEPROJECT_API ADWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void AttackEvent();
	virtual void AttackEvent_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void FireProjectile();
	virtual void FireProjectile_Implementation();

	UFUNCTION(BlueprintPure, Category = Bool)
		class ADCharacter_Base* GetPlayer() const 
	{ 
		if (PlayerRef != nullptr) return PlayerRef;
		return nullptr;
	}
	void SetPlayer(class ADCharacter_Base* character);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FWeaponData WeaponData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(BlueprintReadOnly)
		class ADCharacter_Base* PlayerRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float WeaponCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		TSubclassOf<class ADProjectile> Projectile;
};
