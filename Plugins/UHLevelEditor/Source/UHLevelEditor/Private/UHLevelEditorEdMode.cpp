// Copyright https://github.com/travmygit/UnrealHammer. All Rights Reserved.

#include "UHLevelEditorEdMode.h"
#include "UI/UHLevelEditorUISettings.h"
#include "UI/UHLevelEditorEdModeToolkit.h"

#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

//////////////////////////////////////////////////////////////////////////
// FUHLevelEditorEdMode

const FEditorModeID FUHLevelEditorEdMode::EditorModeID = TEXT("UHLevelEditorEdMode");

FUHLevelEditorEdMode::FUHLevelEditorEdMode()
	: UISettings(nullptr)
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
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), EdgeColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), Transform.TransformPosition(FVector(X, ComponentCountY * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (X == ComponentCountX * QuadsPerComponent)
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(X, 0, 0)), Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), CornerColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector(X, CornerSize * ComponentSize, 0)), Transform.TransformPosition(FVector(X, (ComponentCountY - CornerSize) * ComponentSize, 0)), EdgeColour, SDPG_Foreground);
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
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), EdgeColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), Transform.TransformPosition(FVector(ComponentCountX * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->SetHitProxy(NULL);
				}
				else if (Y == ComponentCountY * QuadsPerComponent)
				{
					PDI->DrawLine(Transform.TransformPosition(FVector(0, Y, 0)), Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), CornerColour, SDPG_Foreground);
					PDI->DrawLine(Transform.TransformPosition(FVector(CornerSize * ComponentSize, Y, 0)), Transform.TransformPosition(FVector((ComponentCountX - CornerSize) * ComponentSize, Y, 0)), EdgeColour, SDPG_Foreground);
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

TSharedRef<FUICommandList> FUHLevelEditorEdMode::GetToolkitCommands() const
{
	checkSlow(Toolkit.IsValid());
	return Toolkit->GetToolkitCommands();
}

void FUHLevelEditorEdMode::SetCurrentToolMode(FName InToolModeName)
{
	if (CurrentToolMode != InToolModeName)
	{
		CurrentToolMode = InToolModeName;
	}
}

void FUHLevelEditorEdMode::SetCurrentTool(FName InToolName)
{
	if (CurrentTool != InToolName)
	{
		CurrentTool = InToolName;
	}
}

void FUHLevelEditorEdMode::SetCurrentBrush(FName InBrushName)
{
	if (CurrentBrush != InBrushName)
	{
		CurrentBrush = InBrushName;
	}
}

FName FUHLevelEditorEdMode::GetCurrentToolModeName() const
{
	return CurrentToolMode;
}

FName FUHLevelEditorEdMode::GetCurrentToolName() const
{
	return CurrentTool;
}

FName FUHLevelEditorEdMode::GetCurrentBrushName() const
{
	return CurrentBrush;
}
