// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "Animation/AnimInstance.h"
#include "DZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API UDZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDZombieAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlayHitMontage();
public:
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurPawnSpeed;
	//Animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, Meta = (AllowPrivateAccess = true))
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, Meta = (AllowPrivateAccess = true))
		class UAnimMontage* Hit01Montage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, Meta = (AllowPrivateAccess = true))
		class UAnimMontage* Hit02Montage;
	
};
