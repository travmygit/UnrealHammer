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

protected:
	TSharedPtr<SUHLevelEditorWidget> LandscapeEditorWidgets;
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

	TSharedPtr<SErrorText> Error;
	TSharedPtr<IDetailsView> DetailsPanel;
	TWeakPtr<FUHLevelEditorEdModeToolkit> ParentToolkit;
};