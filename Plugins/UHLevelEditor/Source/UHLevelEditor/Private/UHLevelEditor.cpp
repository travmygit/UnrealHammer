// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UHLevelEditor.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorDetails.h"

#define LOCTEXT_NAMESPACE "FUHLevelEditorModule"

void FUHLevelEditorModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FUHLevelEditorEdMode>(FUHLevelEditorEdMode::EditorModeID, LOCTEXT("UHLevelEditorEdModeName", "UHLevelEditorEdMode"), FSlateIcon(), true);

	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("UHLevelEditorUISettings", FOnGetDetailCustomizationInstance::CreateStatic(&FUHLevelEditorDetails::MakeInstance));
}

void FUHLevelEditorModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FUHLevelEditorEdMode::EditorModeID);

	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout("UHLevelEditorUISettings");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUHLevelEditorModule, UHLevelEditor)