#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A2.generated.h"

UCLASS()
class CLONEACTOR_API AA2 : public AActor
{
	GENERATED_BODY()
	
public:	
	AA2();

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

protected:

	float SpeedX;
	float MaxX;
	float MinX;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeColor();

private:
	void HideActor();
	void ShowActor();

	FTimerHandle ActorTimerHandle;

	FTimerHandle ColorChangeTimerHandle;
	
	FTimerHandle RepeatingColorChangeTimerHandle;

};
