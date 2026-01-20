// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BioPunk : ModuleRules
{
	public BioPunk(ReadOnlyTargetRules Target) : base(Target)
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
			"BioPunk",
			"BioPunk/Variant_Platforming",
			"BioPunk/Variant_Platforming/Animation",
			"BioPunk/Variant_Combat",
			"BioPunk/Variant_Combat/AI",
			"BioPunk/Variant_Combat/Animation",
			"BioPunk/Variant_Combat/Gameplay",
			"BioPunk/Variant_Combat/Interfaces",
			"BioPunk/Variant_Combat/UI",
			"BioPunk/Variant_SideScrolling",
			"BioPunk/Variant_SideScrolling/AI",
			"BioPunk/Variant_SideScrolling/Gameplay",
			"BioPunk/Variant_SideScrolling/Interfaces",
			"BioPunk/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
