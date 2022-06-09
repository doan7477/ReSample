// Fill out your copyright notice in the Description page of Project Settings.


#include "DZombieAnimInstance.h"
#include "Animation/AnimMontage.h"

UDZombieAnimInstance::UDZombieAnimInstance()
{
	CurPawnSpeed = 0.0f;
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ATTACK_MONTAGE(TEXT("/Game/Sample/Enemy/Zombie/Animations/Male/AnimMontage_ZombieAttack_male.AnimMontage_ZombieAttack_male"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>HIT01_MONTAGE(TEXT("/Game/Sample/Enemy/Zombie/Animations/Male/AnimMontage_ZombieHit01_male.AnimMontage_ZombieHit01_male"));
	if (HIT01_MONTAGE.Succeeded())
	{
		Hit01Montage = HIT01_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>HIT02_MONTAGE(TEXT("/Game/Sample/Enemy/Zombie/Animations/Male/AnimMontage_ZombieHit02_male.AnimMontage_ZombieHit02_male"));
	if (HIT02_MONTAGE.Succeeded())
	{
		Hit02Montage = HIT02_MONTAGE.Object;
	}
}

void UDZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UDZombieAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage) == true)
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UDZombieAnimInstance::PlayHitMontage()
{
	if (!Montage_IsPlaying(Hit01Montage) == true)
	{
		
	}
	Montage_Play(Hit01Montage);
}
