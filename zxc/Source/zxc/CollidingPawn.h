// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "CollidingPawnMovementComponent.h"
#include "CollidingPawnSolarSystem.h"
#include "CollidingPawn.generated.h"

UCLASS()
class ZXC_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UParticleSystemComponent* OurParticleSystem;
	class UCollidingPawnMovementComponent* OurMovementComponent;
	UCollidingPawnSolarSystem* SolarSystemComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UStaticMeshComponent* SphereVisual2;
	UStaticMeshComponent* SphereVisual3;
	UStaticMeshComponent* SphereVisual4;
};
