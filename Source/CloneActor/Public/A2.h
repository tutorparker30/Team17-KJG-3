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
	float MoveSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
