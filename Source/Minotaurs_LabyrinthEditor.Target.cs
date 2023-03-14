// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Minotaurs_LabyrinthEditorTarget : TargetRules
{
	public Minotaurs_LabyrinthEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Minotaurs_Labyrinth" } );
	}
}
