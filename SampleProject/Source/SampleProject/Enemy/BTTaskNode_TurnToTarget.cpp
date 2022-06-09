// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"
#include "DZombie.h"
#include "../Characters/DCharacter_Base.h"
#include "DAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Zombie = Cast<ADZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr) EBTNodeResult::Failed;

	auto Target = Cast<ADCharacter_Base>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADAIController::TargetKey));
	if (Target == nullptr) EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Zombie->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Zombie->SetActorRotation(FMath::RInterpTo(Zombie->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
