// Fill out your copyright notice in the Description page of Project Settings.


#include "DAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADAIController::HomePosKey(TEXT("HomePos"));
const FName ADAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ADAIController::TargetKey(TEXT("Target"));

ADAIController::ADAIController()
{
	RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_OBJECT(TEXT("/Game/Sample/Enemy/Zombie/BB_DZombie.BB_DZombie"));
	if (BB_OBJECT.Succeeded()) BBAsset = BB_OBJECT.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_OBJECT(TEXT("/Game/Sample/Enemy/Zombie/BT_DZombie.BT_DZombie"));
	if (BT_OBJECT.Succeeded()) BTAsset = BT_OBJECT.Object;
}

void ADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ADAIController::OnRepeatTimer, RepeatInterval, true);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree!!!"));
		}
	}
}

/*void ADAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}*/

void ADAIController::OnRepeatTimer()
{
	auto CurPawn = GetPawn();

	/*UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr) return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
	}*/

}
