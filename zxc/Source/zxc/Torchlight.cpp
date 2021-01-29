#include "Torchlight.h"

// Sets default values
ATorchlight::ATorchlight()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATorchlight::BeginPlay()
{
	Super::BeginPlay();
	ATorchlight::AddFuel();
}

void ATorchlight::AddFuel_Implementation()
{
	GetWorldTimerManager().SetTimer(torchlightHandle, this, &ATorchlight::DouseWithWater, 10.0f, true);
}

void ATorchlight::DouseWithWater_Implementation()
{
	GetWorldTimerManager().ClearTimer(torchlightHandle);
}