// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "DAIController.h"
#include "DZombie.h"


UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Zombie = Cast<ADZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie == nullptr) return EBTNodeResult::Failed;

	Zombie->Attack();
	IsAttacking = true;
	Zombie->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecond)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecond);
	if (!IsAttacking) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
