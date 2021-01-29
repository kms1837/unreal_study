// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSpawnActor.h"

// Sets default values
AMovementSpawnActor::AMovementSpawnActor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Simulation Generates Hit Event
	//CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("MovementBox"));
	//CollisionComponent->OnComponentHit.AddDynamic(this, &AMovementSpawnActor::OnHit);
	// 구체의 콜리전 반경을 설정합니다.
	//CollisionComponent->InitBoxExtent(FVector(20, 10, 5));
	// 루트 컴포넌트를 콜리전 컴포넌트로 설정합니다.
	//RootComponent = CollisionComponent;

}

// Called when the game starts or when spawned
void AMovementSpawnActor::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AMovementSpawnActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaTime;
	NewLocation.X += DeltaTime;
	NewLocation.Y += DeltaHeight * speed;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}