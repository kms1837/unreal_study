// Fill out your copyright notice in the Description page of Project Settings.
#include "UIController.h"

void AUIController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}