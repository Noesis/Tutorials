// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HUDViewModel.h"
#include "MenuViewModel.h"

#include "MainViewModel.generated.h"

/**
 * Main ViewModel for the application
 */
UCLASS(Blueprintable)
class LAYEREDUI_API UMainViewModel : public UObject
{
	GENERATED_BODY()

	UMainViewModel(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	UHUDViewModel* HUD;
	
	UPROPERTY()
	UMenuViewModel* Menu;

	UFUNCTION()
	void ToggleMenu();
};
