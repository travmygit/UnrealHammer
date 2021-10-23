// Copyright Epic Games, Inc. All Rights Reserved.

#include "UHLevelEditorEdModeToolkit.h"
#include "UHLevelEditorEdMode.h"
#include "Engine/Selection.h"
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
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnButtonClick, InOffset);
		}
	};

	LandscapeEditorWidgets = SNew(SUHLevelEditor, SharedThis(this));

	FModeToolkit::Init(InitToolkitHost);
}

FName FUHLevelEditorEdModeToolkit::GetToolkitFName() const
{
	return FName("UHLevelEditorEdMode");
}

FText FUHLevelEditorEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("UHLevelEditorEdModeToolkit", "DisplayName", "UHLevelEditorEdMode Tool");
}

class FEdMode* FUHLevelEditorEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId);
}

TSharedPtr<class SWidget> FUHLevelEditorEdModeToolkit::GetInlineContent() const
{
	return LandscapeEditorWidgets;
}

//////////////////////////////////////////////////////////////////////////
// SUHLevelEditor

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SUHLevelEditor::Construct(const FArguments& InArgs, TSharedRef<FUHLevelEditorEdModeToolkit> InParentToolkit)
{
	ParentToolkit = InParentToolkit;

	FUHLevelEditorEdMode* EdMode = GetEditorMode();
	if (EdMode)
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);
		DetailsPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
		DetailsPanel->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SUHLevelEditor::GetIsPropertyVisible));
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

class FUHLevelEditorEdMode* SUHLevelEditor::GetEditorMode() const
{
	return (FUHLevelEditorEdMode*)GLevelEditorModeTools().GetActiveMode(FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId);
}

bool SUHLevelEditor::GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
