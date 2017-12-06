////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Generated header include
#include "LoginFunctionLibrary.generated.h"

UCLASS()
class ULoginFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "NoesisGui", meta = (HidePin = "Target"))
	static bool IsPasswordValid(UObject* PasswordBox, FString AccountName);
};
