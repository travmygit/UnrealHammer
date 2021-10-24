// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdMode

class FUHLevelEditorEdMode : public FEdMode
{
public:

	const static FEditorModeID EditorModeID;

	class UUHLevelEditorUISettings* UISettings;

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
