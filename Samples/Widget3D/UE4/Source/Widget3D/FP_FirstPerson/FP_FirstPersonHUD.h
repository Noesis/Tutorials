// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FP_FirstPersonHUD.generated.h"

UCLASS(Blueprintable)
class AFP_FirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFP_FirstPersonHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor CrosshairColor;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

