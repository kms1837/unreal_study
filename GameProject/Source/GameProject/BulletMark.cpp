// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMark.h"

// Sets default values
ABulletMark::ABulletMark()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Mark"));

	burnParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BurnParticle"));
	burnParticle->SetupAttachment(RootComponent);
	
	//GetComponents<Collision

	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void ABulletMark::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletMark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABulletMark::Burn(UParticleSystem* setBurnParticle) {
	burnParticle->SetTemplate(setBurnParticle);
}

