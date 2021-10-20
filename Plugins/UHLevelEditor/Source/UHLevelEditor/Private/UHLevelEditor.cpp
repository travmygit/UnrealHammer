// Copyright Epic Games, Inc. All Rights Reserved.

#include "UHLevelEditor.h"
#include "UHLevelEditorEdMode.h"

#define LOCTEXT_NAMESPACE "FUHLevelEditorModule"

void FUHLevelEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FUHLevelEditorEdMode>(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId, LOCTEXT("UHLevelEditorEdModeName", "UHLevelEditorEdMode"), FSlateIcon(), true);
}

void FUHLevelEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUHLevelEditorModule, UHLevelEditor)