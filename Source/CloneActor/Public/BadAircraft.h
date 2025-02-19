#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "BadAircraft.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class CLONEACTOR_API ABadAircraft : public APawn
{
	GENERATED_BODY()

public:
	ABadAircraft();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DroneMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float MaxSpeed = 1200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float Acceleration = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float Deceleration = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight|Gravity")
	float GravityZ = -500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight|Friction")
	float AirFriction = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight|Friction")
	float GroundFriction = 8.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flight")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flight")
	bool bIsGrounded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float PitchSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float YawSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float RollSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float MaxPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float MaxRoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flight")
	FRotator RotationRate;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	float ForwardInput;
	float RightInput;
	float UpInput;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleMovement(float DeltaTime);
	void HandleRotation(float DeltaTime);
	void CheckGround(const FHitResult& Hit);

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

};
