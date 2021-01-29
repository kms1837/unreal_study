// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Hero.generated.h"

UCLASS()
class GAMEPROJECT_API AHero : public ACharacter
{
	GENERATED_BODY()

private:
	const float defaultFullDronTime = 10.0f;
	bool alive = true;
	bool droneOnline;

	FVector defaultCameraPosition;
	FVector dronCameraPosition;
	FVector startPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AHero();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, category = "ping")
	TSubclassOf<AActor> PingActor;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* OurCameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DroneCameraComponent;

	UPROPERTY(VisibleAnywhere)
	UWidgetInteractionComponent* MousePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "dron")
	float fullDronTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "dron")
	float dronTime;
	float updateDronTime;
	FTimerHandle dronTimerHandle;

	UFUNCTION(BlueprintPure, Category = "dron")
	float GetDronTimePercent();

	UFUNCTION(BlueprintPure, Category = "dron")
	FText GetDronTimeText();

	void DronInit();
	void DronUpdate();

	void MoveForward(float value);
	void MoveRight(float value);

	void StartJump();
	void StopJump();

	void DroneSwitching();
	void DronSwitchAction();

	void Fire();

	void Hit();

	void Ping();

	void Dead();

	void Respawn();
};
