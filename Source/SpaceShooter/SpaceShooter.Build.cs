// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceShooter : ModuleRules
{
	public SpaceShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SpaceShooter",
			"SpaceShooter/Variant_Platforming",
			"SpaceShooter/Variant_Platforming/Animation",
			"SpaceShooter/Variant_Combat",
			"SpaceShooter/Variant_Combat/AI",
			"SpaceShooter/Variant_Combat/Animation",
			"SpaceShooter/Variant_Combat/Gameplay",
			"SpaceShooter/Variant_Combat/Interfaces",
			"SpaceShooter/Variant_Combat/UI",
			"SpaceShooter/Variant_SideScrolling",
			"SpaceShooter/Variant_SideScrolling/AI",
			"SpaceShooter/Variant_SideScrolling/Gameplay",
			"SpaceShooter/Variant_SideScrolling/Interfaces",
			"SpaceShooter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
