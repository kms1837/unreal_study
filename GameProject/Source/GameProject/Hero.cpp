// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero.h"

AHero::AHero() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->TargetArmLength = 0.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->bEnableCameraRotationLag = true;
	OurCameraSpringArm->CameraLagSpeed = 10.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(OurCameraSpringArm);
	//CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeLocation(FVector(80, 0, 70));

	DroneCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("DroneCamera"));
	DroneCameraComponent->SetupAttachment(OurCameraSpringArm);
	//DroneCameraComponent->SetupAttachment(RootComponent);
	DroneCameraComponent->SetRelativeLocation(FVector(-140, 0, 275));
	DroneCameraComponent->SetRelativeRotation(FRotator(-30, 0, 0));

	MousePoint = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	MousePoint->SetupAttachment(CameraComponent);
	MousePoint->SetRelativeLocation(FVector(0, 0, -15));
	MousePoint->bShowDebug = true;
	MousePoint->DebugColor = FColor(255, 0, 0);

	dronCameraPosition = FVector(-300.0f, 0.0f, 300.0f);

	DronInit();
}

void AHero::BeginPlay() {
	Super::BeginPlay();

	fullDronTime = defaultFullDronTime;

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("player load complete"));
		defaultCameraPosition = CameraComponent->GetRelativeLocation();
		startPosition = GetActorLocation();
	}
}

void AHero::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (GetActorLocation().Z < -300.0f) {
		Dead();
	}
}

void AHero::DronInit() {
	dronTime = 10.0f;
	droneOnline = false;
} // 드론 초기상태

void AHero::DronUpdate() {
	dronTime += updateDronTime;
	dronTime = FMath::Clamp(dronTime, 0.0f, fullDronTime);

	if (dronTime <= 0 || dronTime >= fullDronTime) {
		GetWorldTimerManager().ClearTimer(dronTimerHandle);
	}

	if (dronTime <= 0) {
		DroneSwitching();
	}
}

float AHero::GetDronTimePercent() {
	return dronTime / fullDronTime;
}

FText AHero::GetDronTimeText() {
	FString fullDronTimeText = FString::FromInt(fullDronTime);
	FString currentTimeText = FString::FromInt(dronTime);
	FString dronTimeText = currentTimeText + FString(TEXT("/")) + fullDronTimeText;
	FText text = FText::FromString(dronTimeText);
	return text;
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveY", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveX", this, &AHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHero::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHero::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHero::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHero::StopJump);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AHero::DronSwitchAction);
	PlayerInputComponent->BindAction("Ping", IE_Pressed, this, &AHero::Ping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHero::Fire);
}

void AHero::MoveForward(float value) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AHero::MoveRight(float value) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AHero::StartJump() {
	bPressedJump = true;
}

void AHero::StopJump() {
	bPressedJump = false;
}

void AHero::DronSwitchAction() {
	if (dronTime > 0) {
		DroneSwitching();
	}
}

void AHero::DroneSwitching() {
	droneOnline = !droneOnline;

	//CameraComponent->SetActive(!droneOnline);
	//DroneCameraComponent->SetActive(droneOnline);
	//MousePoint->AttachToComponent(droneOnline? DroneCameraComponent : CameraComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

	//APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//if (OurPlayerController) {
		//const float SmoothBlendTime = 0.75f;
		//OurPlayerController->SetViewTargetWithBlend(CameraComponent, SmoothBlendTime);
	//}
	CameraComponent->SetRelativeLocation(droneOnline ? dronCameraPosition : defaultCameraPosition);

	updateDronTime = droneOnline ? -1.0f : 1.0f;
	GetWorldTimerManager().ClearTimer(dronTimerHandle);
	GetWorldTimerManager().SetTimer(dronTimerHandle, this, &AHero::DronUpdate, 1.0f, true);
}

void AHero::Ping() {
	FHitResult hitResult;
	FVector start = CameraComponent->GetComponentLocation();
	FVector forwardVector = CameraComponent->GetForwardVector();
	FVector end = (start + (forwardVector * 10000.f));
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(this);

	bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, traceParams);

	FVector spawnPoint;
	FRotator spawnRotation;
	GetController()->GetPlayerViewPoint(spawnPoint, spawnRotation);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ping!"));

	if (isHit) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ping!!!"));

		FActorSpawnParameters spanwnParms;
		spawnRotation.Pitch = -180.0f;
		GetWorld()->SpawnActor<AActor>(PingActor, hitResult.Location, spawnRotation, spanwnParms);
	}
}

void AHero::Fire() {
	FHitResult hitResult;
	FVector start = CameraComponent->GetComponentLocation();
	FVector forwardVector = CameraComponent->GetForwardVector();
	FVector end = (start + (forwardVector * 10000.f));
	FCollisionQueryParams traceParams;
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, traceParams);

	if (isHit) {
		AHero* hitActor = Cast<AHero>(hitResult.GetActor());
		if (hitActor != nullptr) {
			hitActor->Hit();
		}
	}
}

void AHero::Hit() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit Character"));
	FVector currentScale = GetActorScale();
	currentScale += FVector(0.1, 0.1, 0.1);
	SetActorScale3D(currentScale);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AActor>(UBoxComponent::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);
}

void AHero::Dead() {
	if (alive) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dead"));
		alive = false;
		Respawn();
	}
}

void AHero::Respawn() {
	alive = true;
	SetActorLocation(startPosition);
}