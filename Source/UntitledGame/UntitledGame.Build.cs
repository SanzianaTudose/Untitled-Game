// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UntitledGame : ModuleRules
{
	public UntitledGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
