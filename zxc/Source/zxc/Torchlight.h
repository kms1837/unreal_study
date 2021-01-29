// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torchlight.generated.h"
/*
타이머 핸들과 약간의 커스텀 이벤트 를 사용하여 (불타는 파티클 시스템 컴포넌트 를 비활성화시키든가 해서) 끌 수 있는 불타는 횃불을 만들어 보세요.
예를 들어 AddFuel 이벤트 를 확장시켜 횃불의 타는 시간을 만듭니다. DouseWithWater 이벤트 는 즉시 종료시켜 앞으로 AddFuel 의 작동을 중지시킵니다. 이 두 기능 모두 Tick 을 사용하지 않고,
핸들을 통한 타이머 실행을 변경하는 것으로 간단히 작성할 수 있습니다.
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
