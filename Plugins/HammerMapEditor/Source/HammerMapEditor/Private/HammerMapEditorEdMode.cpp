// Copyright Epic Games, Inc. All Rights Reserved.

#include "HammerMapEditorEdMode.h"
#include "HammerMapEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId = TEXT("EM_HammerMapEditorEdMode");

FHammerMapEditorEdMode::FHammerMapEditorEdMode()
{

}

FHammerMapEditorEdMode::~FHammerMapEditorEdMode()
{

}

void FHammerMapEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FHammerMapEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FHammerMapEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FHammerMapEditorEdMode::UsesToolkits() const
{
	return true;
}




