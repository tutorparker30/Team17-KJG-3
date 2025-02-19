using UnrealBuildTool;

public class CloneActor : ModuleRules
{
	public CloneActor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG"
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
