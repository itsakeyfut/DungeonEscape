// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("Game Start"));
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	SetShouldMove(false);

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();

	ReachedTarget = CurrentLocation.Equals(TargetLocation);

	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}
}

bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	if (ShouldMove)
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}
}
