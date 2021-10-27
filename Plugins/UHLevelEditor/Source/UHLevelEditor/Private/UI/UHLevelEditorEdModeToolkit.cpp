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

namespace UHLevelEditorEdModeToolkit
{
	static const FName Manage(TEXT("ToolMode_Manage"));
	static const FName Sculpt(TEXT("ToolMode_Sculpt"));
	static const FName Paint(TEXT("ToolMode_Paint"));
}

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdModeToolkit

FUHLevelEditorEdModeToolkit::FUHLevelEditorEdModeToolkit()
{
}

void FUHLevelEditorEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		auto UICommands = FUHLevelEditorUICommands::Get();
		const auto& NameToCommandMap = UICommands.NameToCommandMap;
		TSharedRef<FUICommandList> UICommandList = GetToolkitCommands();

#define MAP_TOOLMODE(InName) UICommandList->MapAction(NameToCommandMap.FindChecked(InName), FUIAction(FExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::OnToolModeChanged, FName(InName)), FCanExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsToolModeEnabled, FName(InName)), FIsActionChecked::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsToolModeActive, FName(InName))));
		MAP_TOOLMODE("ToolMode_Manage");
		MAP_TOOLMODE("ToolMode_Sculpt");
		MAP_TOOLMODE("ToolMode_Paint");
#undef  MAP_TOOLMODE
		
#define MAP_TOOL(InName) UICommandList->MapAction(NameToCommandMap.FindChecked(InName), FUIAction(FExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::OnToolChanged, FName(InName)), FCanExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsToolEnabled, FName(InName)), FIsActionChecked::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsToolActive, FName(InName))));
		MAP_TOOL("Tool_NewLandscape");
		MAP_TOOL("Tool_ResizeLandscape");
		MAP_TOOL("Tool_SelectComponent");
		MAP_TOOL("Tool_AddComponent");
		MAP_TOOL("Tool_DeleteComponent");
		MAP_TOOL("Tool_MoveComponent");

		MAP_TOOL("Tool_Sculpt");
		MAP_TOOL("Tool_Ramp");

		MAP_TOOL("Tool_Paint");
#undef  MAP_TOOL

#define MAP_BRUSH_SET(InName) UICommandList->MapAction(NameToCommandMap.FindChecked(InName), FUIAction(FExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::OnBrushSetChanged, FName(InName)), FCanExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsBrushSetEnabled, FName(InName)), FIsActionChecked::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsBrushSetActive, FName(InName))));
#undef  MAP_BRUSH_SET

#define MAP_BRUSH(InName) UICommandList->MapAction(NameToCommandMap.FindChecked(InName), FUIAction(FExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::OnBrushChanged, FName(InName)), FCanExecuteAction::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsBrushEnabled, FName(InName)), FIsActionChecked::CreateSP(this, &FUHLevelEditorEdModeToolkit::IsBrushActive, FName(InName))));
#undef  MAP_BRUSH

		LandscapeEditorWidgets = SNew(SUHLevelEditorWidget, SharedThis(this));
	}

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

const TArray<FName> FUHLevelEditorEdModeToolkit::PaletteNames = { UHLevelEditorEdModeToolkit::Manage, UHLevelEditorEdModeToolkit::Sculpt, UHLevelEditorEdModeToolkit::Paint };

void FUHLevelEditorEdModeToolkit::GetToolPaletteNames(TArray<FName>& InPaletteName) const
{
	InPaletteName = PaletteNames;
}

FText FUHLevelEditorEdModeToolkit::GetToolPaletteDisplayName(FName PaletteName) const
{
	if (PaletteName == UHLevelEditorEdModeToolkit::Manage)
	{
		return LOCTEXT("Mode.Manage", "Manage");
	}
	else if (PaletteName == UHLevelEditorEdModeToolkit::Sculpt)
	{
		return LOCTEXT("Mode.Sculpt", "Sculpt");
	}
	else if (PaletteName == UHLevelEditorEdModeToolkit::Paint)
	{
		return LOCTEXT("Mode.Paint", "Paint");
	}
	return FText::GetEmpty();
}

void FUHLevelEditorEdModeToolkit::BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder)
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		auto UICommands = FUHLevelEditorUICommands::Get();
		if (PaletteName == UHLevelEditorEdModeToolkit::Manage)
		{
			ToolbarBuilder.BeginSection(UHLevelEditorEdModeToolkit::Manage);
			ToolbarBuilder.AddToolBarButton(UICommands.NewLandscapeTool);
			ToolbarBuilder.AddToolBarButton(UICommands.ResizeLandscapeTool);
			ToolbarBuilder.AddSeparator();
			ToolbarBuilder.AddToolBarButton(UICommands.SelectComponentTool);
			ToolbarBuilder.AddToolBarButton(UICommands.AddComponentTool);
			ToolbarBuilder.AddToolBarButton(UICommands.DeleteComponentTool);
			ToolbarBuilder.AddToolBarButton(UICommands.MoveComponentTool);
			ToolbarBuilder.EndSection();
		}
		else if (PaletteName == UHLevelEditorEdModeToolkit::Sculpt)
		{
			ToolbarBuilder.BeginSection(UHLevelEditorEdModeToolkit::Sculpt);
			ToolbarBuilder.AddToolBarButton(UICommands.SculptTool);
			ToolbarBuilder.AddToolBarButton(UICommands.RampTool);
			ToolbarBuilder.EndSection();
		}
		else if (PaletteName == UHLevelEditorEdModeToolkit::Paint)
		{
			ToolbarBuilder.BeginSection(UHLevelEditorEdModeToolkit::Paint);
			ToolbarBuilder.AddToolBarButton(UICommands.PaintTool);
			ToolbarBuilder.EndSection();
		}
	}
}

void FUHLevelEditorEdModeToolkit::OnToolPaletteChanged(FName PaletteName)
{
	if (PaletteName == UHLevelEditorEdModeToolkit::Manage && !IsToolModeActive(UHLevelEditorEdModeToolkit::Manage))
	{
		OnToolModeChanged(UHLevelEditorEdModeToolkit::Manage);
	}
	else if (PaletteName == UHLevelEditorEdModeToolkit::Sculpt && !IsToolModeActive(UHLevelEditorEdModeToolkit::Sculpt))
	{
		OnToolModeChanged(UHLevelEditorEdModeToolkit::Sculpt);
	}
	else if (PaletteName == UHLevelEditorEdModeToolkit::Paint && !IsToolModeActive(UHLevelEditorEdModeToolkit::Paint))
	{
		OnToolModeChanged(UHLevelEditorEdModeToolkit::Paint);
	}
}

void FUHLevelEditorEdModeToolkit::OnToolModeChanged(FName ToolModeName)
{
	FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//EdMode->SetCurrentToolMode(ToolModeName);
	}
}

bool FUHLevelEditorEdModeToolkit::IsToolModeEnabled(FName ToolModeName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		// Manage is the only mode enabled if we have no landscape
		if (ToolModeName == UHLevelEditorEdModeToolkit::Manage /*|| ((EdMode->GetLandscapeList().Num() > 0) && EdMode->CanEditCurrentTarget())*/)
		{
			return true;
		}
	}
	return false;
}

bool FUHLevelEditorEdModeToolkit::IsToolModeActive(FName ToolModeName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentToolMode->ToolModeName == ToolModeName;
		return true;
	}
	return false;
}

void FUHLevelEditorEdModeToolkit::OnToolChanged(FName ToolName)
{
	FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//EdMode->SetCurrentTool(ToolName);
	}
}

bool FUHLevelEditorEdModeToolkit::IsToolEnabled(FName ToolName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		if (ToolName == "Tool_NewLandscape" /*|| (EdMode->GetLandscapeList().Num() > 0)*/)
		{
			return true;
		}
	}
	return false;
}

bool FUHLevelEditorEdModeToolkit::IsToolActive(FName ToolName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentTool->ToolName == ToolName;
		return true;
	}
	return false;
}

void FUHLevelEditorEdModeToolkit::OnBrushSetChanged(FName BrushSetName)
{
	FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//EdMode->SetCurrentBrushSet(BrushSetName);
	}
}

bool FUHLevelEditorEdModeToolkit::IsBrushSetEnabled(FName BrushSetName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentTool->ValidBrushes.Contains(BrushSetName);
		return true;
	}
	return false;
}

bool FUHLevelEditorEdModeToolkit::IsBrushSetActive(FName BrushSetName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentTool->BrushSetName == BrushSetName;
		return true;
	}
	return false;
}

void FUHLevelEditorEdModeToolkit::OnBrushChanged(FName BrushName)
{
	FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//EdMode->SetCurrentBrush(BrushName);
	}
}

bool FUHLevelEditorEdModeToolkit::IsBrushEnabled(FName BrushName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentTool->ValidBrushes.Contains(BrushName);
		return true;
	}
	return false;
}

bool FUHLevelEditorEdModeToolkit::IsBrushActive(FName BrushName) const
{
	const FUHLevelEditorEdMode* EdMode = (FUHLevelEditorEdMode*)GetEditorMode();
	if (EdMode)
	{
		//return EdMode->CurrentTool->BrushName == BrushName;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// SUHLevelEditorWidget

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SUHLevelEditorWidget::Construct(const FArguments& InArgs, TSharedRef<FUHLevelEditorEdModeToolkit> InParentToolkit)
{
	ParentToolkit = InParentToolkit;

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
				.IsEnabled(this, &SUHLevelEditorWidget::GetLevelEditorIsEnabled)
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

bool SUHLevelEditorWidget::GetLevelEditorIsEnabled() const
{
	const FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		Error->SetError(GetErrorText());
		return true;
	}
	return false;
}

FText SUHLevelEditorWidget::GetErrorText() const
{
	const FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		EUHLevelEditorEditingState EditingState = EUHLevelEditorEditingState::Enabled;
		switch (EditingState)
		{
			case EUHLevelEditorEditingState::SIEWorld:
			{
				if (EdMode->UISettings->NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None)
				{
					return LOCTEXT("IsSimulatingError_create", "Can't create landscape while simulating!");
				}
				else
				{
					return LOCTEXT("IsSimulatingError_edit", "Can't edit landscape while simulating!");
				}
			}
			case EUHLevelEditorEditingState::PIEWorld:
			{
				if (EdMode->UISettings->NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None)
				{
					return LOCTEXT("IsPIEError_create", "Can't create landscape in PIE!");
				}
				else
				{
					return LOCTEXT("IsPIEError_edit", "Can't edit landscape in PIE!");
				}
			}
			case EUHLevelEditorEditingState::BadFeatureLevel:
			{
				if (EdMode->UISettings->NewLandscapeMethod != EUHLevelEditorNewLandscapeMethod::None)
				{
					return LOCTEXT("IsFLError_create", "Can't create landscape with a feature level less than SM4!");
				}
				else
				{
					return LOCTEXT("IsFLError_edit", "Can't edit landscape with a feature level less than SM4!");
				}
			}
			case EUHLevelEditorEditingState::NoLandscape:
			{
				return LOCTEXT("NoLandscapeError", "No Landscape!");
			}
			case EUHLevelEditorEditingState::Enabled:
			{
				return FText::GetEmpty();
			}
			default:
				checkNoEntry();
		}
	}
	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE
