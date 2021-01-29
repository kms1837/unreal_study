// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트는 물리에 반응하는 구체가 됩니다
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	/*
	USphereComponent* SphereComponent2 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	SphereComponent2->InitSphereRadius(40.0f);

	USphereComponent* SphereComponent3 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere2"));
	SphereComponent3->InitSphereRadius(40.0f);*/

	// 구체가 어딨는지 확인할 수 있도록 메시 컴포넌트 생성 및 위치 조정
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	
	UStaticMeshComponent* SphereVisual2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1"));
	SphereVisual2->SetupAttachment(RootComponent);
	UStaticMeshComponent* SphereVisual3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2"));
	SphereVisual3->SetupAttachment(RootComponent);
	UStaticMeshComponent* SphereVisual4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3"));
	SphereVisual4->SetupAttachment(RootComponent);
	/*
	애셋 경로를 하드코딩하는 것은 별로 바람직한 애셋 로드 방식이 아닙니다. 클래스에서 컴포넌트 를 사용한다면 보통은 코드로 컴포넌트 자체를 만든 다음, 언리얼 에디터 에서 선택하는 것이 낫습니다.
	*/
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));

		SphereVisual2->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual2->SetRelativeLocation(FVector(60.0f, 30.0f, -40.0f));
		SphereVisual2->SetWorldScale3D(FVector(0.4f));

		SphereVisual3->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual3->SetRelativeLocation(FVector(120.0f, 60.0f, -40.0f));
		SphereVisual3->SetWorldScale3D(FVector(0.4f));

		SphereVisual4->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual4->SetRelativeLocation(FVector(180.0f, 90.0f, -40.0f));
		SphereVisual4->SetWorldScale3D(FVector(0.4f));
	}

	// 활성화 또는 비활성화시킬 수 있는 파티클 시스템 생성
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
	//RelativeRotation
	// 스프링 암을 사용하여 카메라에 부드럽고 자연스러운 모션을 적용합니다.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// 카메라를 만들어 스프링 암에 붙입니다.
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// 기본 플레이어 컨트롤 획득
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 무브먼트 컴포넌트 인스턴스를 생성하고, 루트를 업데이트하라 이릅니다.
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	SolarSystemComponent = CreateDefaultSubobject<UCollidingPawnSolarSystem>(TEXT("asd"));
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);

	InputComponent->BindAxis("MoveX", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveY", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);

}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}
