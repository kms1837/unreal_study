// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ���𰡸� ���� ���� ��Ʈ ������Ʈ�� ����ϴ�
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// ī�޶�� ���̴� ������Ʈ�� ����ϴ�
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// ��Ʈ ������Ʈ�� ī�޶�� ���̴� ������Ʈ�� ���Դϴ�. ī�޶� �̰� �� ȸ����ŵ�ϴ�.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	speed = 0;
	pressXMoveKey = false;
	pressYMoveKey = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle growing and shrinking based on our "Grow" action
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// Grow to double size over the course of one second
			CurrentScale += DeltaTime;
		}
		else
		{
			// Shrink half as fast as we grow
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// Make sure we never drop below our starting size, or increase past double size.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

	if (pressXMoveKey || pressYMoveKey) {
		speed += 1.0f;
	}

	if (!pressXMoveKey && !pressYMoveKey) {
		speed = 0.0f;
	}

	speed = FMath::Clamp(speed, 0.0f, 500.0f);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// "Grow" Ű�� �����ų� �� �� �����մϴ�
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// "MoveX" �� "MoveY" �� �̵� ���� ���� �� ������ �����մϴ�
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	// �ʴ� 100 ������ �� �Ǵ� �ڷ� �����Դϴ�
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
	ImmediateCompletion(AxisValue);

	pressXMoveKey = AxisValue != 0 ? true : false;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	// �ʴ� 100 ������ ������ �Ǵ� �������� �����Դϴ�
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * speed;
	ImmediateCompletion(AxisValue);

	pressYMoveKey = AxisValue != 0 ? true : false;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}

void AMyPawn::ImmediateCompletion(float AxisValue) {
	if (bGrowing && AxisValue != 0) {
		OurVisibleComponent->SetWorldScale3D(FVector(2.0f));
	}
}

