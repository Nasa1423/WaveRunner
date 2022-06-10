// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WaveRunner : ModuleRules
{
	public WaveRunner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });
	}
}
