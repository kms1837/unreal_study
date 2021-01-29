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
	�̺�Ʈ �� ����Ǹ� Ÿ�� Ʈ���������� �̵� �Ǵ� ȸ���ϴ� ���� �� ����ϴ�. �̴� ���ӿ��� �̵� �÷����̳� ������ ���� �� �ֽ��ϴ�. �� �̺�Ʈ �� Ÿ�̸� �� ��������, ���� �� ���� ��ġ�� �̵���Ű�� 2�� �̺�Ʈ �� �ߵ���ŵ�ϴ�. �ϵ��ڵ��� ���� ����ϱ� ���ٴ� ������ (UPROPERTY �� ����) ����� ������ ����մϴ�.
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
