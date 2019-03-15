////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LoginFunctionLibrary.h"

// Noesis includes
#include "NoesisRuntime.h"

ULoginFunctionLibrary::ULoginFunctionLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

bool ULoginFunctionLibrary::IsPasswordValid(UObject* InPasswordBox, FString AccountName)
{
    Noesis::Ptr<Noesis::BaseComponent> BaseComponent = NoesisCreateComponentForUObject(InPasswordBox);
    if (BaseComponent)
    {
        Noesis::PasswordBox* PasswordBox = Noesis::DynamicCast<Noesis::PasswordBox*>(BaseComponent.GetPtr());
        if (PasswordBox)
        {
            return (FCStringAnsi::Strcmp("12345", PasswordBox->GetPassword()) == 0) && (AccountName == TEXT("noesis"));
        }
    }

    return false;
}
