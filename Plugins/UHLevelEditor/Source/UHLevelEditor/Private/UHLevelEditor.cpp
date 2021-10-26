// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UHLevelEditor.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorDetails.h"
#include "UI/UHLevelEditorUICommands.h"

#define LOCTEXT_NAMESPACE "FUHLevelEditorModule"

void FUHLevelEditorModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FUHLevelEditorEdMode>(FUHLevelEditorEdMode::EditorModeID, LOCTEXT("UHLevelEditorEdModeName", "UHLevelEditorEdMode"), FSlateIcon(), true);

	FUHLevelEditorUICommands::Register();

	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("UHLevelEditorUISettings", FOnGetDetailCustomizationInstance::CreateStatic(&FUHLevelEditorDetails::MakeInstance));
}

void FUHLevelEditorModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FUHLevelEditorEdMode::EditorModeID);

	FUHLevelEditorUICommands::Unregister();

	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout("UHLevelEditorUISettings");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUHLevelEditorModule, UHLevelEditor)