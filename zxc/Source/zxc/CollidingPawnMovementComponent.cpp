// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

/*
이 TickComponent 함수는 UPawnMovementComponent 클래스에 제공되는 강력한 기능을 몇 가지 활용하고 있습니다.

ConsumeInputVector 는 미동 입력을 저장하는 데 사용할 내장 변수 값을 보고 및 소거합니다.

SafeMoveUpdatedComponent 는 언리얼 엔진 피직스를 사용하여 입체 장애물을 피해 Pawn Movement Component 를 이동시킵니다.

SlideAlongSurface 는 이동하다가 충돌 발생시 그냥 제자리에 멈춰 벽이나 경사로에 "달라붙기" 보다는, 그 표면을 타고 부드럽게 미끄러지도록 하는 데 관련된 물리 계산 처리를 합니다.

Pawn Movement Components 에는 설명할 만한 기능이 더 있지만, 이 튜토리얼 범위에는 필요치 않습니다. Floating Pawn Movement, Spectator Pawn Movement, Character Movement Component 같은 다른 클래스를 살펴보면
추가적인 용례나 개념을 찾아볼 수 있습니다.

*/

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 모든 것이 아직 유효한지, 이동 가능한지 확인합니다.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // ACollidingPawn::Tick 에 설정한 무브먼트 벡터를 구(한 뒤 소거)합니다.
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // 무언가에 부딛혔으면, 돌아가 봅니다.
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
};