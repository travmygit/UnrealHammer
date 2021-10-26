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

	TMap<FName, TSharedPtr<FUICommandInfo>> NameToCommandMap;
	
	static const FName UIContext;
};