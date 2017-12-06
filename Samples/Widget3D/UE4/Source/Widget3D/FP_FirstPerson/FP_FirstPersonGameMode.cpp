// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPersonGameMode.h"
#include "FP_FirstPersonHUD.h"
#include "FP_FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFP_FirstPersonGameMode::AFP_FirstPersonGameMode()
{
	DefaultPawnClass = AFP_FirstPersonCharacter::StaticClass();

	HUDClass = AFP_FirstPersonHUD::StaticClass();
}
