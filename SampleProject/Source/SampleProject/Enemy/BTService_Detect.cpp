// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "DAIController.h"
#include "DZombie.h"
#include "../Characters/DCharacter_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;

	if (World == nullptr) return;
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam);

	if (bResult == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADAIController::TargetKey, nullptr);
		for (auto OR : OverlapResults)
		{
			ADCharacter_Base* Player = Cast<ADCharacter_Base>(OR.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADAIController::TargetKey, Player);
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				//DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
