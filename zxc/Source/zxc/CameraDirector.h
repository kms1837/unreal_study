// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic)
struct FCameraS {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere)
	AActor* Camera;
	UPROPERTY(EditAnywhere)
	int runningtime;
};

UCLASS()
class ZXC_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int cameraCount = 3;
	int currentCamera = 0;

	UPROPERTY(EditAnywhere)
	FCameraS Cameras[3];

	float TimeToNextCameraChange;

};
