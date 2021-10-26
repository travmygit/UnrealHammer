#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorUICommands

class FUHLevelEditorUICommands : public TCommands<FUHLevelEditorUICommands>
{
public:

	FUHLevelEditorUICommands();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin TCommands interface
	virtual void RegisterCommands() override;
	//~ End TCommands interface
	//////////////////////////////////////////////////////////////////////////

public:
	TSharedPtr<FUICommandInfo> ManageMode;
	TSharedPtr<FUICommandInfo> SculptMode;
	TSharedPtr<FUICommandInfo> PaintMode;

	TSharedPtr<FUICommandInfo> NewLandscapeTool;
	TSharedPtr<FUICommandInfo> ResizeLandscapeTool;
	TSharedPtr<FUICommandInfo> SelectComponentTool;
	TSharedPtr<FUICommandInfo> AddComponentTool;
	TSharedPtr<FUICommandInfo> DeleteComponentTool;
	TSharedPtr<FUICommandInfo> MoveComponentTool;

	TSharedPtr<FUICommandInfo> SculptTool;
	TSharedPtr<FUICommandInfo> RampTool;

	TSharedPtr<FUICommandInfo> PaintTool;

	TMap<FName, TSharedPtr<FUICommandInfo>> NameToCommandMap;
	
	static const FName UIContext;
};