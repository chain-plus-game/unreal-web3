// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class web3 : ModuleRules
{
    public web3(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Json",
                "JsonUtilities",
                "Http",
                "WebSockets"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "WebSockets"
            }
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            }
            );
    }
}
