// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Interview_1 : ModuleRules
{
	public Interview_1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput",
				"RemoteControl", "RemoteControlWebInterface", "RemoteControlCommon" });
	}
}
