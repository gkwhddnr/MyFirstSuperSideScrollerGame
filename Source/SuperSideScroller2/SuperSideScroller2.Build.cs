// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SuperSideScroller2 : ModuleRules
{
	public SuperSideScroller2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
