// Copyright Epic Games, Inc. All Rights Reserved.

#include "UHLevelEditorEdMode.h"
#include "UHLevelEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId = TEXT("EM_UHLevelEditorEdMode");

FUHLevelEditorEdMode::FUHLevelEditorEdMode()
{

}

FUHLevelEditorEdMode::~FUHLevelEditorEdMode()
{

}

void FUHLevelEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FUHLevelEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FUHLevelEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FUHLevelEditorEdMode::UsesToolkits() const
{
	return true;
}




