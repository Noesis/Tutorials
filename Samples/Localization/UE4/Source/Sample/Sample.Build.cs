////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class Sample : ModuleRules
{
    public Sample(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "SampleGame.h";

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
    }
}
