// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class PROJECT_B1EditorTarget : TargetRules
{
	public PROJECT_B1EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "PROJECT_B1" } );
	}
}
