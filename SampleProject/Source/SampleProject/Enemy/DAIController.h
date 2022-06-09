// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SampleProject.h"
#include "AIController.h"
#include "DAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT_API ADAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADAIController();
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
};
