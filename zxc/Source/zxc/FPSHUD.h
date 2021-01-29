// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZXC_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
public:
	// HUD 에 대한 주요 드로 콜입니다.
	virtual void DrawHUD() override;
protected:
	// 화면 중앙에 그려질 것입니다.
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
	
};
