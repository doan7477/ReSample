// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FProjectileData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		class UStaticMesh* ProjectileMesh;
	UPROPERTY(EditAnywhere, Category = Data)
		float Damage;
	UPROPERTY(EditAnywhere, Category = Data)
		float Speed;
	UPROPERTY(EditAnywhere, Category = Data)
		bool bCriticalDamage;
};

UCLASS()
class SAMPLEPROJECT_API ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(VisibleAnywhere, Category = Collision)
		class USphereComponent* SphereCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UParticleSystemComponent* ProjectileTrail;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FProjectileData ProjectileData;
	UPROPERTY(VisibleAnywhere, Category = Projectile)
		class UProjectileMovementComponent* ProjectMovement;
};
