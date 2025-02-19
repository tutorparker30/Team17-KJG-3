#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class CLONEACTOR_API AMineItem : public ABaseItem
{	GENERATED_BODY()

public:
	AMineItem();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionDamage;

	bool bHasExploded;
	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
	
};
