// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackingActor.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogTest, Display, All)

UCLASS()
class ZXC_API ATrackingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/*
	이벤트 가 실행되면 타깃 트랜스폼으로 이동 또는 회전하는 액터 를 만듭니다. 이는 게임에서 이동 플랫폼이나 문으로 사용될 수 있습니다. 그 이벤트 에 타이머 를 가동시켜, 액터 를 원래 위치로 이동시키는 2차 이벤트 를 발동시킵니다. 하드코딩된 값을 사용하기 보다는 가급적 (UPROPERTY 를 통해) 노출된 변수를 사용합니다.
	*/

	void Tracking();
	void BackPosition();

	UPROPERTY(EditAnywhere)
	int32 BackPositionTime;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	FVector originPosition;

	FTimerHandle BackTimerHandle;
};
