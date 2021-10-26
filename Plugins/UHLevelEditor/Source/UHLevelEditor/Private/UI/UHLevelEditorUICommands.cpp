#include "UI/UHLevelEditorUICommands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "UHLevelEditorUICommands"

const FName FUHLevelEditorUICommands::UIContext = TEXT("UHLevelEditor");

FUHLevelEditorUICommands::FUHLevelEditorUICommands()
	: TCommands<FUHLevelEditorUICommands>
	(
		FUHLevelEditorUICommands::UIContext,
		LOCTEXT("UHLevelEditor", "UHLevelEditor"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	)
{
}

void FUHLevelEditorUICommands::RegisterCommands()
{
	UI_COMMAND(ManageMode, "Mode - Manage", "", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("ToolMode_Manage", ManageMode);
	UI_COMMAND(SculptMode, "Mode - Sculpt", "", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("ToolMode_Sculpt", SculptMode);
	UI_COMMAND(PaintMode, "Mode - Paint", "", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("ToolMode_Paint", PaintMode);

	UI_COMMAND(NewLandscapeTool, "New", "Create or import a new landscape", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_NewLandscape", NewLandscapeTool);
	UI_COMMAND(ResizeLandscapeTool, "Resize", "Change Component Size", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_ResizeLandscape", ResizeLandscapeTool);
	UI_COMMAND(SelectComponentTool, "Select", "Select components to use with other tools", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_SelectComponent", SelectComponentTool);
	UI_COMMAND(AddComponentTool, "Add", "Add components to the landscape", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_AddComponent", AddComponentTool);
	UI_COMMAND(DeleteComponentTool, "Delete", "Delete components from the landscape, leaving a hole", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_DeleteComponent", DeleteComponentTool);
	UI_COMMAND(MoveComponentTool, "Move", "Move landscape components to a landscape proxy in the currently active streaming level, so that they can be streamed in/out independently of the rest of the landscape", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_MoveComponent", MoveComponentTool);

	UI_COMMAND(SculptTool, "Sculpt", "Sculpt height data.\n\nCtrl+Click to Raise, Ctrl+Shift_Click to lower.", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_Sculpt", SculptTool);
	UI_COMMAND(RampTool, "Ramp", "Creates a ramp between two points.", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_Ramp", RampTool);

	UI_COMMAND(PaintTool, "Paint", "Paint weight data.\n\nCtrl+Click to paint, Ctrl+Shift+Click to erase.", EUserInterfaceActionType::RadioButton, FInputChord());
	NameToCommandMap.Add("Tool_Paint", PaintTool);
}

#undef LOCTEXT_NAMESPACE