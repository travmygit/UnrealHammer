// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"
#include "Widgets/SCompoundWidget.h"

class FUHLevelEditorEdModeToolkit;
class SUHLevelEditorWidget;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdModeToolkit

class FUHLevelEditorEdModeToolkit : public FModeToolkit
{
public:

	FUHLevelEditorEdModeToolkit();
	
	//////////////////////////////////////////////////////////////////////////
	//~ Begin FModeToolkit interface
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;
	//~ End FModeToolkit interface
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IToolkit interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override;
	//~ End IToolkit interface
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//~ Begin FModeToolkit interface
	virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;
	virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;
	virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;
	virtual void OnToolPaletteChanged(FName PaletteName) override;
	//~ End FModeToolkit interface
	//////////////////////////////////////////////////////////////////////////

protected:
	void OnToolModeChanged(FName ModeName);
	bool IsToolModeEnabled(FName ModeName) const;
	bool IsToolModeActive(FName ModeName) const;

private:
	TSharedPtr<SUHLevelEditorWidget> LandscapeEditorWidgets;

	static const TArray<FName> PaletteNames;
};

//////////////////////////////////////////////////////////////////////////
// SUHLevelEditor

class SUHLevelEditorWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUHLevelEditorWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<FUHLevelEditorEdModeToolkit> InParentToolkit);

protected:
	class FUHLevelEditorEdMode* GetEditorMode() const;
	bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;
	bool GetLevelEditorIsEnabled() const;
	FText GetErrorText() const;

	TSharedPtr<SErrorText> Error;
	TSharedPtr<IDetailsView> DetailsPanel;
	TWeakPtr<FUHLevelEditorEdModeToolkit> ParentToolkit;
};