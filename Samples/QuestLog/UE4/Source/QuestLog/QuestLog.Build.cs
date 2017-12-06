////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class QuestLog : ModuleRules
{
	public QuestLog(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "QuestLogGame.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Noesis", "NoesisRuntime" });
	}
}
