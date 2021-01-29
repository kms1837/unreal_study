// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torchlight.generated.h"
/*
Ÿ�̸� �ڵ�� �ణ�� Ŀ���� �̺�Ʈ �� ����Ͽ� (��Ÿ�� ��ƼŬ �ý��� ������Ʈ �� ��Ȱ��ȭ��Ű�簡 �ؼ�) �� �� �ִ� ��Ÿ�� ȶ���� ����� ������.
���� ��� AddFuel �̺�Ʈ �� Ȯ����� ȶ���� Ÿ�� �ð��� ����ϴ�. DouseWithWater �̺�Ʈ �� ��� ������� ������ AddFuel �� �۵��� ������ŵ�ϴ�. �� �� ��� ��� Tick �� ������� �ʰ�,
�ڵ��� ���� Ÿ�̸� ������ �����ϴ� ������ ������ �ۼ��� �� �ֽ��ϴ�.
*/

UCLASS()
class ZXC_API ATorchlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorchlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void AddFuel();

	UFUNCTION(BlueprintNativeEvent)
	void DouseWithWater();

	virtual void AddFuel_Implementation();

	virtual void DouseWithWater_Implementation();

	FTimerHandle torchlightHandle;

};
