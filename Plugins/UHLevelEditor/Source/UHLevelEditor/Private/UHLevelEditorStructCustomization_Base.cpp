#include "UHLevelEditorStructCustomization_Base.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "UHLevelEditorEdMode.h"

FUHLevelEditorEdMode* FUHLevelEditorStructCustomization_Base::GetEditorMode()
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId);
}
