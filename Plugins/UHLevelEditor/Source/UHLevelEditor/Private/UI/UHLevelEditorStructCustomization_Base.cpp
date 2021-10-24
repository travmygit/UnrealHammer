// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorStructCustomization_Base.h"
#include "UHLevelEditorEdMode.h"

#include "EditorModeManager.h"
#include "EditorModes.h"

FUHLevelEditorEdMode* FUHLevelEditorStructCustomization_Base::GetEditorMode()
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EditorModeID);
}
