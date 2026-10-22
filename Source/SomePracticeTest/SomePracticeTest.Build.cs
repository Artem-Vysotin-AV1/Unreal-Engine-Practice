// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SomePracticeTest : ModuleRules
{
	public SomePracticeTest(ReadOnlyTargetRules Target) : base(Target)
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
			"SomePracticeTest",
			"SomePracticeTest/Variant_Platforming",
			"SomePracticeTest/Variant_Platforming/Animation",
			"SomePracticeTest/Variant_Combat",
			"SomePracticeTest/Variant_Combat/AI",
			"SomePracticeTest/Variant_Combat/Animation",
			"SomePracticeTest/Variant_Combat/Gameplay",
			"SomePracticeTest/Variant_Combat/Interfaces",
			"SomePracticeTest/Variant_Combat/UI",
			"SomePracticeTest/Variant_SideScrolling",
			"SomePracticeTest/Variant_SideScrolling/AI",
			"SomePracticeTest/Variant_SideScrolling/Gameplay",
			"SomePracticeTest/Variant_SideScrolling/Interfaces",
			"SomePracticeTest/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
