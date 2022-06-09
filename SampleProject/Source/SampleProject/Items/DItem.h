// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "GameFramework/Actor.h"
#include "../Core/CommonStruct.h"
#include "DItem.generated.h"

UCLASS()
class SAMPLEPROJECT_API ADItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UFUNCTION()
	void OnCharacterOverlap(class UPrimitiveComponent* OverlapComp, class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepHitResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Collision)
		class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Data)
		TSubclassOf<class ADWeapon> WeaponItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int ItemID;
};
