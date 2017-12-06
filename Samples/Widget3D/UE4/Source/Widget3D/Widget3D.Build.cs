////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class Widget3D : ModuleRules
{
	public Widget3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Widget3DGame.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Noesis", "NoesisRuntime" });
	}
}
