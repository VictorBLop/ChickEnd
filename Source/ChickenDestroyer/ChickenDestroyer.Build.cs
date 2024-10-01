// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChickenDestroyer : ModuleRules
{
	public ChickenDestroyer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AIModule", "NavigationSystem" });
	}
}
