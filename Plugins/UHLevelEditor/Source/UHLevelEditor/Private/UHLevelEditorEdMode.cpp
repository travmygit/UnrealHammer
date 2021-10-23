// Copyright Epic Games, Inc. All Rights Reserved.

#include "UHLevelEditorEdMode.h"
#include "UHLevelEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "HitProxies.h"
#include "UHLevelEditorUISettings.h"

//////////////////////////////////////////////////////////////////////////
// EUHNewLandscapeEdge

enum class EUHNewLandscapeEdge : uint8
{
	None,

	// Edges
	X_Negative,
	X_Positive,
	Y_Negative,
	Y_Positive,

	// Corners
	X_Negative_Y_Negative,
	X_Positive_Y_Negative,
	X_Negative_Y_Positive,
	X_Positive_Y_Positive,
};

//////////////////////////////////////////////////////////////////////////
// HUHNewLandscapeGrabHandleProxy

struct HUHNewLandscapeGrabHandleProxy : public HHitProxy
{
	DECLARE_HIT_PROXY();

	EUHNewLandscapeEdge Edge;

	HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge InEdge) :
		HHitProxy(HPP_Wireframe),
		Edge(InEdge)
	{
	}

	virtual EMouseCursor::Type GetMouseCursor() override
	{
		switch (Edge)
		{
		case EUHNewLandscapeEdge::X_Negative:
		case EUHNewLandscapeEdge::X_Positive:
			return EMouseCursor::ResizeLeftRight;
		case EUHNewLandscapeEdge::Y_Negative:
		case EUHNewLandscapeEdge::Y_Positive:
			return EMouseCursor::ResizeUpDown;
		case EUHNewLandscapeEdge::X_Negative_Y_Negative:
		case EUHNewLandscapeEdge::X_Positive_Y_Positive:
			return EMouseCursor::ResizeSouthEast;
		case EUHNewLandscapeEdge::X_Negative_Y_Positive:
		case EUHNewLandscapeEdge::X_Positive_Y_Negative:
			return EMouseCursor::ResizeSouthWest;
		}

		return EMouseCursor::SlashedCircle;
	}
};

IMPLEMENT_HIT_PROXY(HUHNewLandscapeGrabHandleProxy, HHitProxy)

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdMode

const FEditorModeID FUHLevelEditorEdMode::EM_UHLevelEditorEdModeId = TEXT("EM_UHLevelEditorEdMode");

FUHLevelEditorEdMode::FUHLevelEditorEdMode()
	: UISettings(nullptr)
	, NewLandscapePreviewMode(EUHNewLandscapePreviewMode::NewLandscape)
{
	UISettings = NewObject<UUHLevelEditorUISettings>(GetTransientPackage(), NAME_None, RF_Transactional);
	UISettings->Init(this);
}

FUHLevelEditorEdMode::~FUHLevelEditorEdMode()
{
	UISettings = nullptr;
}

void FUHLevelEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FUHLevelEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FUHLevelEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

void FUHLevelEditorEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	// Render landscape paint mesh
	{
		static const float        CornerSize = 0.33f;
		static const FLinearColor CornerColour(1.0f, 1.0f, 0.5f);
		static const FLinearColor EdgeColour(1.0f, 1.0f, 0.0f);
		static const FLinearColor ComponentBorderColour(0.0f, 0.85f, 0.0f);
		static const FLinearColor InnerColour(0.0f, 0.25f, 0.0f);

		const int32 ComponentCountX = UISettings->NewLandscape_ComponentCount.X;
		const int32 ComponentCountY = UISettings->NewLandscape_ComponentCount.Y;
		const int32 QuadsPerComponent = UISettings->NewLandscape_ComponentSize;
		const float ComponentSize = QuadsPerComponent;
		const FVector Offset = UISettings->NewLandscape_Location + FTransform(UISettings->NewLandscape_Rotation, FVector::ZeroVector, UISettings->NewLandscape_Scale).TransformVector(FVector(-ComponentCountX * ComponentSize / 2, -ComponentCountY * ComponentSize / 2, 0));
		const FTransform Transform = FTransform(UISettings->NewLandscape_Rotation, Offset, UISettings->NewLandscape_Scale);

		const ELevelViewportType ViewportType = ((FEditorViewportClient*)Viewport->GetClient())->ViewportType;

		if (ViewportType == LVT_Perspective || ViewportType == LVT_OrthoXY || ViewportType == LVT_OrthoNegativeXY)
		{
			for (int32 X = 0; X <= ComponentCountX * QuadsPerComponent; X++)
			{
				if (X == 0)
				{
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Negative_Y_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), EdgeColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Negative_Y_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), Transform.TransformPosition(FVector(X, ComponentCountY * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (X == ComponentCountX * QuadsPerComponent)
				{
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Positive_Y_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), EdgeColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Positive_Y_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), Transform.TransformPosition(FVector(X, ComponentCountY * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (X % QuadsPerComponent == 0)
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, ComponentCountY * ComponentSize, 0)), ComponentBorderColour, SDPG_Foreground);
				}
				else
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, ComponentCountY * ComponentSize, 0)), InnerColour, SDPG_World);
				}
			}
		}
		else
		{
			// Don't allow dragging to resize in side-view
			// and there's no point drawing the inner lines as only the outer is visible
			PDI->DrawLine(Transform.TransformPosition(FVector(0, 0, 0)), Transform.TransformPosition(FVector(0, ComponentCountY * ComponentSize, 0)), EdgeColour, SDPG_World);
			PDI->DrawLine(Transform.TransformPosition(FVector(ComponentCountX * QuadsPerComponent, 0, 0)), Transform.TransformPosition(FVector(ComponentCountX * QuadsPerComponent, ComponentCountY * ComponentSize, 0)), EdgeColour, SDPG_World);
		}

		if (ViewportType == LVT_Perspective || ViewportType == LVT_OrthoXY || ViewportType == LVT_OrthoNegativeXY)
		{
			for (int32 Y = 0; Y <= ComponentCountY * QuadsPerComponent; Y++)
			{
				if (Y == 0)
				{
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Negative_Y_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::Y_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), EdgeColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Positive_Y_Negative));
					PDI->DrawLine(Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (Y == ComponentCountY * QuadsPerComponent)
				{
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Negative_Y_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::Y_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), EdgeColour, SDPG_Foreground);
					PDI->SetHitProxy(new HUHNewLandscapeGrabHandleProxy(EUHNewLandscapeEdge::X_Positive_Y_Positive));
					PDI->DrawLine(Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (Y % QuadsPerComponent == 0)
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, Y, 0)), ComponentBorderColour, SDPG_Foreground);
				}
				else
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, Y, 0)), InnerColour, SDPG_World);
				}
			}
		}
		else
		{
			// Don't allow dragging to resize in side-view
			// and there's no point drawing the inner lines as only the outer is visible
			PDI->DrawLine(Transform.TransformPosition(FVector(0, 0, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, 0, 0)), EdgeColour, SDPG_World);
			PDI->DrawLine(Transform.TransformPosition(FVector(0, ComponentCountY * QuadsPerComponent, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, ComponentCountY * QuadsPerComponent, 0)), EdgeColour, SDPG_World);
		}
	}
}

bool FUHLevelEditorEdMode::UsesToolkits() const
{
	return true;
}

void FUHLevelEditorEdMode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdMode::AddReferencedObjects(Collector);

	Collector.AddReferencedObject(UISettings);
}



