////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class NineSliceModule : ModuleRules
{
    public NineSliceModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "NineSliceGame.h";

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Noesis", "NoesisRuntime" });
    }
}
