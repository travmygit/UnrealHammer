// Copyright Epic Games, Inc. All Rights Reserved.

#include "HammerMapEditor.h"
#include "HammerMapEditorEdMode.h"

#define LOCTEXT_NAMESPACE "FHammerMapEditorModule"

void FHammerMapEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FHammerMapEditorEdMode>(FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId, LOCTEXT("HammerMapEditorEdModeName", "Hammer Map Editor"), FSlateIcon(), true);
}

void FHammerMapEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHammerMapEditorModule, HammerMapEditor)