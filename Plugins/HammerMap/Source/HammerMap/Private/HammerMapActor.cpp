#include "HammerMapActor.h"

AHammerMapActor::AHammerMapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent0 = CreateDefaultSubobject<USceneComponent>("SceneComponent0");
	RootComponent = SceneComponent0;
	RootComponent->Mobility = EComponentMobility::Static;
}

void AHammerMapActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHammerMapActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHammerMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHammerMapActor::InitializeMap(const FIntPoint& NewMapSize)
{
	MapSize = NewMapSize;
}
