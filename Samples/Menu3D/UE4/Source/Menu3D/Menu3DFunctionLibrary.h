////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Engine includes
#include "Kismet/BlueprintFunctionLibrary.h"

// Generated header include
#include "Menu3DFunctionLibrary.generated.h"

UCLASS()
class UMenu3DFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "NoesisGui", meta = (HidePin = "Target"))
	static void SetFocus(UObject* ElementToFocus);
};
