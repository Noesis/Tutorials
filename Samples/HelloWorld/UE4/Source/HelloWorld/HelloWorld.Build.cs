////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class HelloWorld : ModuleRules
{
	public HelloWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "HelloWorldGame.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Noesis", "NoesisRuntime" });
	}
}
