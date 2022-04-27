#pragma once

#include "CoreMinimal.h"
#include "Components/PropertyViewBase.h"
#include "Misc/NotifyHook.h"
#include "PropertyEditorDelegates.h"
#include "HammerMapEditorUISettingsDetailsView.generated.h"

/**
 * The details view allows you to display the value of an object properties.
 */
UCLASS()
class HAMMERMAPEDITOR_API UHammerMapEditorUISettingsDetailsView : public UPropertyViewBase, public FNotifyHook
{
	GENERATED_BODY()

public:
	/** True if we allow filtering through search and the filter dropdown menu. */
	UPROPERTY(EditAnywhere, Category = "View")
	bool bAllowFiltering = false;
	
	/** The default column width */
	UPROPERTY(EditAnywhere, Category = "View")
	float ColumnWidth = 0.65f;

	/** Which categories to show in the details panel. If both this and the Properties To Show whitelist are empty, all properties will show. */
	UPROPERTY(EditAnywhere, Category = "View")
	TArray<FName> CategoriesToShow;

	/** Which properties to show in the details panel. If both this and the Categories To Show whitelist are empty, all properties will show. */
	UPROPERTY(EditAnywhere, Category = "View")
	TArray<FName> PropertiesToShow;

	//~ UPropertyViewBase interface
private:
	virtual void BuildContentWidget() override;
	virtual void OnObjectChanged() override;
	//~ End of UPropertyViewBase interface

public:
	//~ UWidget interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UWidget interface

	//~ FNotifyHook interface
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	//~ End of FNotifyHook interface

	//~ UObject interface
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End of UObject interface

protected:
	void ToggleWhitelistedProperties();
	bool IsRowVisibilityFiltered() const;
	bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;
	bool GetIsRowVisible(FName InRowName, FName InParentName) const;

private:
	TSharedPtr<IDetailsView> DetailViewWidget;

	/** Showing properties in this details panel works by whitelisting categories and properties. This flag enables you to show all properties without needing to specify. */
	UPROPERTY()
	bool bShowOnlyWhitelisted = true;
};
