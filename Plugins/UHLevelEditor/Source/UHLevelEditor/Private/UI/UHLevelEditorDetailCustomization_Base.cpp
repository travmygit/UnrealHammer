// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorDetailCustomization_Base.h"
#include "UHLevelEditorEdMode.h"

#include "EditorModeManager.h"
#include "EditorModes.h"
#include "DetailLayoutBuilder.h"

FUHLevelEditorEdMode* FUHLevelEditorDetailCustomization_Base::GetEditorMode()
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EditorModeID);
}

bool FUHLevelEditorDetailCustomization_Base::IsToolActive(FName ToolName)
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return true;
	}
	return false;
}

bool FUHLevelEditorDetailCustomization_Base::IsBrushSetActive(FName BrushSetName)
{
	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		return true;
	}
	return false;
}
