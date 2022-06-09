// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API UBTTaskNode_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
