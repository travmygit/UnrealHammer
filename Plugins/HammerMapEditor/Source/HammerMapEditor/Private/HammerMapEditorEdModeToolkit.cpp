// Copyright Epic Games, Inc. All Rights Reserved.

#include "HammerMapEditorEdModeToolkit.h"
#include "HammerMapEditorEdMode.h"
#include "HammerMapEditorSettings.h"
#include "Panel/HammerMapEditorMainPanel.h"

#include "WidgetBlueprint.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FHammerMapEditorEdModeToolkit"

FHammerMapEditorEdModeToolkit::FHammerMapEditorEdModeToolkit()
{
}

void FHammerMapEditorEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	auto HammerMapEditorSettings = GetDefault<UHammerMapEditorSettings>();
	auto MainPanelRef = HammerMapEditorSettings->MainPanel;
	if (MainPanelRef.IsValid())
	{
		UWidgetBlueprint* MainPanel = Cast<UWidgetBlueprint>(MainPanelRef.TryLoad());
		if (MainPanel)
		{
			UHammerMapEditorMainPanel* CreatedUMGWidget = nullptr;
			UClass* BlueprintClass = MainPanel->GeneratedClass;
			TSubclassOf<UHammerMapEditorMainPanel> MainPanelClass = BlueprintClass;
			auto World = GEditor->GetEditorWorldContext().World();
			if (World && MainPanelClass)
			{
				CreatedUMGWidget = CreateWidget<UHammerMapEditorMainPanel>(World, MainPanelClass);
			}

			if (CreatedUMGWidget)
			{
				SAssignNew(ToolkitWidget, SVerticalBox)
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					[
						CreatedUMGWidget->TakeWidget()
					];
			}
		}
	}

	FModeToolkit::Init(InitToolkitHost);
}

FName FHammerMapEditorEdModeToolkit::GetToolkitFName() const
{
	return FName("HammerMapEditorEdMode");
}

FText FHammerMapEditorEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("HammerMapEditorEdModeToolkit", "DisplayName", "HammerMapEditorEdMode Tool");
}

class FEdMode* FHammerMapEditorEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FHammerMapEditorEdMode::EM_HammerMapEditorEdModeId);
}

#undef LOCTEXT_NAMESPACE
