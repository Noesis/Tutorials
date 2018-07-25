////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LoginFunctionLibrary.h"

ULoginFunctionLibrary::ULoginFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool ULoginFunctionLibrary::IsPasswordValid(UObject* InPasswordBox, FString AccountName)
{
	Noesis::Ptr<Noesis::BaseComponent> BaseComponent = NoesisCreateComponentForUObject(InPasswordBox);
	if (BaseComponent)
	{
		Noesis::PasswordBox* PasswordBox = NsDynamicCast<Noesis::PasswordBox*>(BaseComponent.GetPtr());
		if (PasswordBox)
		{
			return (FCStringAnsi::Strcmp("noesis", PasswordBox->GetPassword()) == 0) && (AccountName == TEXT("NoesisGUI"));
		}
	}

	return false;
}
