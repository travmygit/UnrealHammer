// Copyright Epic Games, Inc. All Rights Reserved.

#include "HammerMapEditor.h"
#include "HammerMapEditorEdMode.h"
#include "HammerMapEditorSettings.h"
#include "HammerMapEditorUISettings.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"

#define LOCTEXT_NAMESPACE "FHammerMapEditorModule"

void FHammerMapEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FHammerMapEditorEdMode>(FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId, LOCTEXT("HammerMapEditorEdModeName", "Hammer Map Editor"), FSlateIcon(), true);

	// Register plugin settings.
	RegisterSettings();
}

void FHammerMapEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId);

	// Unregister plugin settings.
	UnregisterSettings();
}

void FHammerMapEditorModule::RegisterSettings()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings("Editor", "Plugins", "HammerMapEditor",
			LOCTEXT("HammerMapEditorSettingsName", "HammerMapEditor"),
			LOCTEXT("HammerMapEditorSettingsDescription", "Configure HammerMapEditor plug-in."),
			GetMutableDefault<UHammerMapEditorSettings>()
		);

		SettingsModule->RegisterSettings("Editor", "Plugins", "HammerMapEditorUISettings",
			LOCTEXT("HammerMapEditorUISettingsName", "HammerMapEditorUISettings"),
			LOCTEXT("HammerMapEditorUISettingsDescription", "Configure HammerMapEditor UI settings."),
			GetMutableDefault<UHammerMapEditorUISettings>()
		);
	}
}

void FHammerMapEditorModule::UnregisterSettings()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "HammerMapEditor");
		SettingsModule->UnregisterSettings("Editor", "Plugins", "HammerMapEditorUISettings");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHammerMapEditorModule, HammerMapEditor)