#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BadAircraft.generated.h"

UCLASS()
class CLONEACTOR_API ABadAircraft : public APawn
{
	GENERATED_BODY()

public:
	ABadAircraft();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
