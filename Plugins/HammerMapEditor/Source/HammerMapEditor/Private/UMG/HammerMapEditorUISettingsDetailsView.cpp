#include "HammerMapEditorUISettingsDetailsView.h"
#include "IDetailsView.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "ObjectEditorUtils.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UHammerMapEditorUISettingsDetailsView


void UHammerMapEditorUISettingsDetailsView::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	DetailViewWidget.Reset();
}


void UHammerMapEditorUISettingsDetailsView::BuildContentWidget()
{
	DetailViewWidget.Reset();

	if (!GetDisplayWidget().IsValid())
	{
		return;
	}

	bool bCreateMissingWidget = true;
	FText MissingWidgetText = LOCTEXT("EditorWidget", "Editor Only");

	if (GIsEditor)
	{
		UObject* ViewedObject = GetObject();
		if (ViewedObject == nullptr)
		{
			bool bIsLazyObjectNull = LazyObject.IsNull();
			if (bIsLazyObjectNull)
			{
				MissingWidgetText = LOCTEXT("UndefinedObject", "Undefined Object");
			}
			else
			{
				MissingWidgetText = LOCTEXT("UnloadedObject", "Unloaded Object");
			}
		}
		else
		{
			FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

			FDetailsViewArgs DetailsViewArgs;
			DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
			DetailsViewArgs.bUpdatesFromSelection = false;
			DetailsViewArgs.bLockable = false;
			DetailsViewArgs.bShowPropertyMatrixButton = false;
			DetailsViewArgs.NotifyHook = this;
			DetailsViewArgs.bAllowFavoriteSystem = false;
			DetailsViewArgs.bShowModifiedPropertiesOption = false;
			DetailsViewArgs.bShowKeyablePropertiesOption = true;
			DetailsViewArgs.bShowAnimatedPropertiesOption = true;
			DetailsViewArgs.bShowScrollBar = true;
			DetailsViewArgs.bForceHiddenPropertyVisibility = false;

			DetailsViewArgs.bAllowSearch = bAllowFiltering;
			DetailsViewArgs.bShowOptions = bAllowFiltering;
			DetailsViewArgs.ColumnWidth = ColumnWidth;
			DetailsViewArgs.bShowCustomFilterOption = PropertiesToShow.Num() != 0 || CategoriesToShow.Num() != 0;
			
			DetailViewWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
			
			DetailViewWidget->SetCustomFilterLabel(LOCTEXT("ShowAllParameters", "Show All Parameters"));
			DetailViewWidget->SetCustomFilterDelegate(FSimpleDelegate::CreateUObject(this, &UHammerMapEditorUISettingsDetailsView::ToggleWhitelistedProperties));

			DetailViewWidget->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateUObject(this, &UHammerMapEditorUISettingsDetailsView::GetIsPropertyVisible));
			DetailViewWidget->SetIsCustomRowVisibilityFilteredDelegate(FIsCustomRowVisibilityFiltered::CreateUObject(this, &UHammerMapEditorUISettingsDetailsView::IsRowVisibilityFiltered));
			DetailViewWidget->SetIsCustomRowVisibleDelegate(FIsCustomRowVisible::CreateUObject(this, &UHammerMapEditorUISettingsDetailsView::GetIsRowVisible));
			DetailViewWidget->SetObject(ViewedObject);
			if (DetailViewWidget.IsValid())
			{
				GetDisplayWidget()->SetContent(DetailViewWidget.ToSharedRef());
				bCreateMissingWidget = false;
			}
			else
			{
				MissingWidgetText = LOCTEXT("UnknownError", "Unknown Error");
			}
		}
	}

	if (bCreateMissingWidget)
	{
		GetDisplayWidget()->SetContent(
			SNew(STextBlock)
			.Text(MissingWidgetText)
		);
	}
}


void UHammerMapEditorUISettingsDetailsView::OnObjectChanged()
{
	UObject* ViewedObject = GetObject();
	if (DetailViewWidget.IsValid() && ViewedObject != nullptr)
	{
		DetailViewWidget->SetObject(ViewedObject);
	}
	else
	{
		BuildContentWidget();
	}
}


void UHammerMapEditorUISettingsDetailsView::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	FNotifyHook::NotifyPostChange(PropertyChangedEvent, PropertyThatChanged);

	FName PropertyName = PropertyThatChanged ? PropertyThatChanged->GetFName() : NAME_None;
	OnPropertyChangedBroadcast(PropertyName);
}


void UHammerMapEditorUISettingsDetailsView::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (IsDesignTime())
	{
		if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UHammerMapEditorUISettingsDetailsView, bAllowFiltering)
			|| PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UHammerMapEditorUISettingsDetailsView, ColumnWidth))
		{
			SoftObjectPath = LazyObject.Get();
			AsynBuildContentWidget();
		}
	}
}


void UHammerMapEditorUISettingsDetailsView::ToggleWhitelistedProperties()
{
	bShowOnlyWhitelisted = !bShowOnlyWhitelisted;
	if (DetailViewWidget.IsValid())
	{
		DetailViewWidget->ForceRefresh();
	}
}


bool UHammerMapEditorUISettingsDetailsView::IsRowVisibilityFiltered() const
{
	return bShowOnlyWhitelisted && (PropertiesToShow.Num() > 0 || CategoriesToShow.Num() > 0);
}

bool UHammerMapEditorUISettingsDetailsView::GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
    if (!IsRowVisibilityFiltered())
	{
		return true;
	}
	if (PropertiesToShow.Contains(PropertyAndParent.Property.GetFName()))
	{
		return true;
	}
	if (CategoriesToShow.Contains(FObjectEditorUtils::GetCategoryFName(&PropertyAndParent.Property)))
	{
		return true;
	}
	return false;
}

bool UHammerMapEditorUISettingsDetailsView::GetIsRowVisible(FName InRowName, FName InParentName) const
{
    if (!IsRowVisibilityFiltered())
	{
		return true;
	}
	if (PropertiesToShow.Contains(InRowName))
	{
		return true;
	}
	if (CategoriesToShow.Contains(InParentName))
	{
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
