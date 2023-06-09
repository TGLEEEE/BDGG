// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BDGG : ModuleRules
{
	public BDGG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "OnlineSubsystemSteam", "OnlineSubsystem", "GeometryCollectionEngine", "FieldSystemEngine", "Niagara", "AnimGraphRuntime" });
	}
}
