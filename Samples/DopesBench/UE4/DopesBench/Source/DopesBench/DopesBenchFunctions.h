////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Engine includes
#include "Kismet/BlueprintFunctionLibrary.h"

// Generated header include
#include "DopesBenchFunctions.generated.h"

UCLASS()
class UDopesBenchFunctions: public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintCallable, Category = "NoesisGUI", meta = (HidePin = "Target"))
    static void OnTick(UCanvasPanel* DopesCanvas, UTextBlock* DopesText, int RunningTest);

    UFUNCTION(BlueprintCallable, Category = "NoesisGUI", meta = (HidePin = "Target"))
    static void StartTest(UCanvasPanel* DopesCanvas, UTextBlock* DopesText);

    UFUNCTION(BlueprintCallable, Category = "NoesisGUI", meta = (HidePin = "Target"))
    static void StopTest(UTextBlock* DopesText);
};
