// Fill out your copyright notice in the Description page of Project Settings.


#include "DAnimInstance.h"
#include "Animation/AnimMontage.h"

UDAnimInstance::UDAnimInstance()
{
	CurPawnSpeed = 0.0f;
}

void UDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UDAnimInstance::PlayAttackMontage(UAnimMontage* AttackMontage)
{
	if (IsValid(AttackMontage) == false) return;
	Montage_Play(AttackMontage);
}

void UDAnimInstance::UpdateAimPitchAndYaw_Implementation(float PitchValue, float YawValue, bool bPitch, bool bYaw, float YawClampMin, float YawClampMax)
{
}
