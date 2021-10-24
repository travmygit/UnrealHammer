// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"
#include "IDetailCustomization.h"
#include "PropertyHandle.h"
#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorDetailCustomization_Base.h"

class FUHLevelEditorEdMode;
class IDetailLayoutBuilder;

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorDetailCustomization_NewLandscape

class FUHLevelEditorDetailCustomization_NewLandscape : public FUHLevelEditorDetailCustomization_Base
{
public:
	
	FUHLevelEditorDetailCustomization_NewLandscape();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//~ End IDetailCustomization interface
	//////////////////////////////////////////////////////////////////////////

public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	ECheckBoxState NewLandscapeModeIsChecked(EUHLevelEditorNewLandscapeMethod NewLandscapeMethod) const;
	void OnNewLandscapeModeChanged(ECheckBoxState NewCheckedState, EUHLevelEditorNewLandscapeMethod NewLandscapeMethod);
};