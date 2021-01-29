// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnSolarSystem.h"


// Sets default values for this component's properties
UCollidingPawnSolarSystem::UCollidingPawnSolarSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolarMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	staticMesh->SetStaticMesh(SphereVisualAsset.Object);
	staticMesh->SetMobility(EComponentMobility::Movable);
	staticMesh->SetWorldScale3D(FVector(0.01f, 0.01f, 0.1f));
}


// Called when the game starts
void UCollidingPawnSolarSystem::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCollidingPawnSolarSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector parentLocation = GetOwner()->GetActorLocation();

	FVector direction = FVector((FMath::Cos(GetWorld()->GetRealTimeSeconds()) * 200.0f) + parentLocation.X, 
								(FMath::Sin(GetWorld()->GetRealTimeSeconds()) * 200.0f) + parentLocation.Y, 
								0.0f);

	staticMesh->SetWorldLocation(direction);
	//GetOwner()->SetActorRelativeLocation(direction);

	//test->GetComponentTransform().GetLocation();


	//USceneComponent::GetComponentTransform

	//FVector direction = FVector((FMath::Cos(rad) * 100.0f) + currentPosition.X, (FMath::Sin(rad) * 100.0f) + currentPosition.Y, 0.0f);
	//FVector setPosition = direction * DeltaTime;
}

