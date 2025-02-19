#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class CLONEACTOR_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverHeadWidget;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	
	UFUNCTION()
	void Look(const FInputActionValue& value);
	
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	void OnDeath();
	void UpdateOverHeadHP();

public:

	UFUNCTION(BlueprintCallable, Category = "Debuff")
	void ApplySpeedDebuff(float Duration, float SpeedMultiplier);
	UFUNCTION(BlueprintCallable, Category = "Debuff")
	void ApplyReverseControlsDebuff(float Duration);

protected:

	UFUNCTION()
	void OnSpeedDebuffEnd();
	UFUNCTION()
	void OnReverseControlsDebuffEnd();

	void UpdateCharacterSpeed();

private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;

	bool bSprinting;

	int32 SpeedDebuffStack;
	float CurrentSpeedMultiplier;

	int32 ReverseControlStack;
	bool bIsControlReversed;

};
