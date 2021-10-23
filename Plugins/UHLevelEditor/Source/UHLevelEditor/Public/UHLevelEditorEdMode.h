// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

//////////////////////////////////////////////////////////////////////////
// EUHNewLandscapePreviewMode

enum class EUHNewLandscapePreviewMode : uint8
{
	None,
	NewLandscape,
	ImportLandscape,
};

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdMode

class FUHLevelEditorEdMode : public FEdMode
{
public:

	const static FEditorModeID EM_UHLevelEditorEdModeId;

	class UUHLevelEditorUISettings* UISettings;

	EUHNewLandscapePreviewMode NewLandscapePreviewMode;

public:

	FUHLevelEditorEdMode();
	virtual ~FUHLevelEditorEdMode();

	//////////////////////////////////////////////////////////////////////////
	//~ Begin FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	//~ End FEdMode interface
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//~ Begin FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FGCObject interface
	//////////////////////////////////////////////////////////////////////////

private:
	

};
