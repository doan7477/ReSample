// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "Animation/AnimInstance.h"
#include "DAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API UDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(class UAnimMontage* AttackMontage);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateAimPitchAndYaw(float PitchValue, float YawValue, bool bPitch, bool bYaw, float YawClampMin, float YawClampMax);

	virtual void UpdateAimPitchAndYaw_Implementation(float PitchValue, float YawValue, bool bPitch, bool bYaw, float YawClampMin, float YawClampMax);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurPawnSpeed;
};
