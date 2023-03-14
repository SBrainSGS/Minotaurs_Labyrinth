// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Minotaurs_LabyrinthTarget : TargetRules
{
	public Minotaurs_LabyrinthTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Minotaurs_Labyrinth" } );
	}
}
