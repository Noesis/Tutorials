////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class SamplesModule : ModuleRules
{
    public SamplesModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "SamplesGame.h";

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
    }
}
