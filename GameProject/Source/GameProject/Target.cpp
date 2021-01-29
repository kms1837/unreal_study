// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATarget::Hit() {
	int randomRange = FMath::RandRange(-200, 200);
	FTransform spawnTransform = FTransform(GetActorRotation(), (GetActorLocation() + FVector(0, randomRange, 0)));
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ATarget>(this->GetClass(), spawnTransform, SpawnParams);
	Destroy();
}
