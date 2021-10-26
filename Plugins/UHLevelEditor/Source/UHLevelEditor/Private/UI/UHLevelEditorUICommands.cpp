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
}

#undef LOCTEXT_NAMESPACE