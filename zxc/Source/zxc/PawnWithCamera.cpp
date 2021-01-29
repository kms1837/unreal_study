// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//컴포넌트를 생성합니다
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//기본 플레이어의 제어권을 획득합니다
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	speed = 100.0f;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;         //0.5 초에 걸쳐 줌인
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //0.25 초에 걸쳐 줌아웃
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//ZoomFactor 에 따라 스프링 암의 길이와 카메라의 시야 블렌딩
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation);
	}

	if (!MovementInput.IsZero())
	{
		//이동 입력 축 값에 초당 100 유닛 스케일을 적용합니다
		MovementInput = MovementInput.GetSafeNormal() * speed;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//"ZoomIn" 에 대한 이벤트를 걸어줍니다
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	InputComponent->BindAction("Run", IE_Pressed, this, &APawnWithCamera::Run);
	InputComponent->BindAction("Run", IE_Released, this, &APawnWithCamera::Walk);

	//네 축에 대한 매 프레임 처리를 걸어줍니다
	InputComponent->BindAxis("MoveX", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveY", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Turn", this, &APawnWithCamera::YawCamera);

}

//입력 함수
void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}

void APawnWithCamera::Run() {
	speed = 300.0f;
}

void APawnWithCamera::Walk() {
	speed = 100.0f;
}