#include "BadAircraft.h"

ABadAircraft::ABadAircraft()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABadAircraft::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABadAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABadAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

