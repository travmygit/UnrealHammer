// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UI/UHLevelEditorEdModeToolkit.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorUISettings.h"
#include "UI/UHLevelEditorUICommands.h"

#include "Engine/Selection.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FUHLevelEditorEdModeToolkit"

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdModeToolkit

FUHLevelEditorEdModeToolkit::FUHLevelEditorEdModeToolkit()
{
}

void FUHLevelEditorEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	LandscapeEditorWidgets = SNew(SUHLevelEditorWidget, SharedThis(this));

	FModeToolkit::Init(InitToolkitHost);
}

FName FUHLevelEditorEdModeToolkit::GetToolkitFName() const
{
	return FName("UHLevelEditorEdModeToolkit");
}

FText FUHLevelEditorEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("UHLevelEditorEdModeToolkit", "DisplayName", "UHLevelEditorEdModeToolkit Tool");
}

class FEdMode* FUHLevelEditorEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EditorModeID);
}

TSharedPtr<class SWidget> FUHLevelEditorEdModeToolkit::GetInlineContent() const
{
	return LandscapeEditorWidgets;
}

//////////////////////////////////////////////////////////////////////////
// SUHLevelEditorWidget

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SUHLevelEditorWidget::Construct(const FArguments& InArgs, TSharedRef<FUHLevelEditorEdModeToolkit> InParentToolkit)
{
	ParentToolkit = InParentToolkit;

	TSharedRef<FUICommandList> CommandList = InParentToolkit->GetToolkitCommands();
	FToolBarBuilder ModeSwitchButtons(CommandList, FMultiBoxCustomization::None);
	{
		ModeSwitchButtons.AddToolBarButton(FUHLevelEditorUICommands::Get().ManageMode, NAME_None, LOCTEXT("Mode.Manage", "Manage"), LOCTEXT("Mode.Manage.Tooltip", "Contains tools to add a new landscape, import/export landscape, add/remove components and manage streaming"));
		ModeSwitchButtons.AddToolBarButton(FUHLevelEditorUICommands::Get().SculptMode, NAME_None, LOCTEXT("Mode.Sculpt", "Sculpt"), LOCTEXT("Mode.Sculpt.Tooltip", "Contains tools that modify the shape of a landscape"));
		ModeSwitchButtons.AddToolBarButton(FUHLevelEditorUICommands::Get().PaintMode, NAME_None, LOCTEXT("Mode.Paint", "Paint"), LOCTEXT("Mode.Paint.Tooltip", "Contains tools that paint materials on to a landscape"));
	}

	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);
		DetailsPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
		DetailsPanel->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SUHLevelEditorWidget::GetIsPropertyVisible));
		DetailsPanel->SetObject(EdMode->UISettings);

		ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 5)
			[
				SAssignNew(Error, SErrorText)
			]
			+ SVerticalBox::Slot()
			.Padding(0)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(0)
				[
					DetailsPanel.ToSharedRef()
				]
			]
		];
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

class FUHLevelEditorEdMode* SUHLevelEditorWidget::GetEditorMode() const
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EditorModeID);
}

bool SUHLevelEditorWidget::GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
