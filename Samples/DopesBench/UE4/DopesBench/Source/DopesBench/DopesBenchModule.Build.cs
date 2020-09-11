// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DopesBenchModule : ModuleRules
{
	public DopesBenchModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "Noesis", "NoesisRuntime" });
	}
}
