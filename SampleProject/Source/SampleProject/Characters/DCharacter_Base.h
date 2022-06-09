// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "GameFramework/Character.h"
#include "../Core/CommonStruct.h"
#include "Components/TimelineComponent.h"
#include "DCharacter_Base.generated.h"

UENUM(BlueprintType)
enum class EFireState : uint8
{
	Idle = 0,
	Firing,
	Reloading,
	Equipping
};

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Walking = 0,
	Running,
	Sprinting,
	Crouching,
	Proning
};

UCLASS()
class SAMPLEPROJECT_API ADCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Bool Get/Set
	UFUNCTION(BlueprintPure, Category = Bool)
		bool IsFiring() const { return bFiring; }
	UFUNCTION(BlueprintCallable, Category = Bool)
		void SetFiring(bool Fire) { bFiring = Fire; }
	UFUNCTION(BlueprintPure, Category = Bool)
		bool IsAttacking() const { return bAttacking; }
	UFUNCTION(BlueprintPure, Category = Bool)
		bool IsAiming() const { return bAiming; }

	bool IsEquipWeapon();
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(class ADWeapon* weapon);
	void AutoAttackEvent();
	void AutoAttackFinish();

	UFUNCTION(BlueprintCallable)
	void MovementMode(EMovementState state);

	UFUNCTION(BlueprintCallable)
	void AnimBPUpdateAimPitchAndYaw(float PitchValue, float YawValue, bool IsPitch, bool IsYaw, float YawMin, float YawMax);

	UFUNCTION(BlueprintCallable)
	void ResetRotation();
private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void Attack();
	void AttackFinish();
	void RunOn();
	void RunOff();
	void FreeViewOn();
	void FreeViewOff();
	void LerpSpeed();
	void AimingOn();
	void AimingOff();
	
	//
	float CalculateAimOffsetYaw();
	void TimeDuringAiming();
	//void SetWeaponState();
	//Timeline
	void SmoothCamTimelineSetting();
public:
	//Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UArrowComponent* ForwardArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneComponent* AimingCamScene;
	//Mesh
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* Head;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* Legs;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* Backpack;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* ExtraEquipment;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USceneComponent* WeaponScene;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class UStaticMeshComponent* Weapon;
	
	//Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		EWeaponType AttackType;
	UPROPERTY(VisibleAnywhere, Category = Attack)
		EFireState FireState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		EMovementState MoveState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float CameraSensitivity;
	
	float CurMaxSpeed;
	bool bEquipWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	class ADWeapon* HasWeapon;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float YawAngleMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float YawAngleMax;

	//TimeLine
	FOnTimelineFloat SmoothCamInterpFunction;
	FOnTimelineEvent SmoothCamTimelineFinish;
	UFUNCTION()
		void SmoothCamInterpReturn(float value);
	UFUNCTION()
		void SmoothCamOnFinish();
	UPROPERTY()
		UTimelineComponent* SmoothCamCurveTimeline;
	UPROPERTY(EditAnywhere, Category = Timeline)
		UCurveFloat* SmoothCamCurveFloat;
private:
	
	bool bFiring;
	FTimerHandle AutoAttackHandle;
	bool bAttacking;
	bool bAiming;
	float TargetWalkSpeed;

protected:
	FVector DirectionToMove = FVector::ZeroVector;
};
