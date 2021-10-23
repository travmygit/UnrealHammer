#include "UHLevelEditorDetailCustomization_Base.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "DetailLayoutBuilder.h"
#include "UHLevelEditorEdMode.h"

FUHLevelEditorEdMode* FUHLevelEditorDetailCustomization_Base::GetEditorMode()
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId);
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
