#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerMapActor.generated.h"

UCLASS()
class HAMMERMAP_API AHammerMapActor : public AActor
{
	GENERATED_BODY()

public:
	AHammerMapActor();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	/// Initialize the map with the given parameters.
	/// @param NewMapSize the size of new map.
	UFUNCTION(BlueprintCallable)
	void InitializeMap(const FIntPoint& NewMapSize);
	
protected:
	/// The size of map.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint MapSize;
};
