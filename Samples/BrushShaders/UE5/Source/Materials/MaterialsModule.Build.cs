////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using UnrealBuildTool;

public class MaterialsModule : ModuleRules
{
    public MaterialsModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "MaterialsGame.h";

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
    }
}
