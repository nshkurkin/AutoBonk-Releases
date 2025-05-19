// Copyright FTL Goats Interactive LLC

using System.IO;
using UnrealBuildTool;

public class AutoBonk : ModuleRules
{
	public AutoBonk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;

		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Error;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"Projects",
			"InputCore",
			"SlateCore",
			"Slate",
			"UMG",
			"DeveloperSettings",
		});

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(new string[] {
				"UnrealEd",
				"LevelEditor"
			});

			PrivateDependencyModuleNames.AddRange(new string[] {
				"EditorStyle",
				"Settings",
				"ContentBrowserData",
			});
		}
	}
}
