// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "GameFramework/Character.h"
#include "DZombie.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	Idle = 0,
	Walk,
	Run,
	Attack,
	Scream,
	Hit,
	Die
};

UENUM(BlueprintType)
enum class EZombieGenderType : uint8
{
	Ukonwn = 0,
	Male,
	Female
};

UCLASS()
class SAMPLEPROJECT_API ADZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual void PossessedBy(AController* NewController) override;
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void HitEvent(float DamageAmount);
	void Die();

	UFUNCTION(BlueprintCallable)
		void HandAttackOnOff(bool on);
	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	//
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USphereComponent* AttackCollision;
	//Type
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Type)
		EZombieGenderType GenderType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		EZombieState State;

	//Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float CurMaxSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float AttackDamage;
};
