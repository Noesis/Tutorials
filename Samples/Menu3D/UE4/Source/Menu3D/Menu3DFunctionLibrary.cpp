////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu3DFunctionLibrary.h"
#include "NoesisRuntime.h"

UMenu3DFunctionLibrary::UMenu3DFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMenu3DFunctionLibrary::SetFocus(UObject* ElementToFocus)
{
	Noesis::BaseComponent* Component = NoesisCreateComponentForUObject(ElementToFocus);
	if (!Component)
	{
		return;
	}

	Noesis::UIElement* Element = (Noesis::UIElement*)Component;
	Element->Focus();
}
