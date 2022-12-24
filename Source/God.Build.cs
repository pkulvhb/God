// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class God : ModuleRules
{
	public God(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "JsonUtilities", "Json" });
	}
}
