// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackingActor.h"

// Sets default values
ATrackingActor::ATrackingActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATrackingActor::BeginPlay()
{
	Super::BeginPlay();
	ATrackingActor::Tracking();
	UE_LOG(LogTest, Log, TEXT("Log Message2"));
	GetWorldTimerManager().SetTimer(BackTimerHandle, this, &ATrackingActor::BackPosition, BackPositionTime, true);
}

void ATrackingActor::Tracking()
{
	originPosition = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	SetActorLocation(TargetLocation);
}

void ATrackingActor::BackPosition()
{
	SetActorLocation(originPosition);
	UE_LOG(LogTest, Log, TEXT("Log Message"));
	GetWorldTimerManager().ClearTimer(BackTimerHandle);
}
