// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RETURN_XENIA : ModuleRules
{
	public RETURN_XENIA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
