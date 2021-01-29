#pragma once

#include "Engine/Classes/Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class ZXC_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

private:
	float moveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���� �̵� ó��
	UFUNCTION()
	void MoveForward(float Value);

	// �¿� �̵� ó��
	UFUNCTION()
	void MoveRight(float Value);

	// Ű�� ������ ���� �÷��׸� �����մϴ�.
	UFUNCTION()
	void StartJump();

	// Ű�� ���� ���� �÷��׸� ����ϴ�.
	UFUNCTION()
	void StopJump();

	void StartRun();
	void StopRun();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// ����Ī �޽� (��), ���� �÷��̾�Ը� ���Դϴ�.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	// �߻� ó��
	UFUNCTION()
	void Fire();

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;
};
