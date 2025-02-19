#include "BadAircraft.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ABadAircraft::ABadAircraft()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionComp->SetSimulatePhysics(false);
	RootComponent = CollisionComp;

	DroneMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMeshComp"));
	DroneMeshComp->SetupAttachment(CollisionComp);
	DroneMeshComp->SetSimulatePhysics(false);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CollisionComp);
	CameraComp->SetRelativeLocation(FVector(-300.f, 0.f, 100.f));

	MaxSpeed = 1200.f;
	Acceleration = 2000.f;
	Deceleration = 800.f;
	GravityZ = -500.f;
	AirFriction = 1.f;
	GroundFriction = 8.f;
	Velocity = FVector::ZeroVector;
	bIsGrounded = false;

	PitchSpeed = 60.f;
	YawSpeed = 90.f;
	RollSpeed = 60.f;
	MaxPitch = 80.f;
	MaxRoll = 60.f;
	RotationRate = FRotator::ZeroRotator;

	ForwardInput = 0.f;
	RightInput = 0.f;
	UpInput = 0.f;

}

void ABadAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement(DeltaTime);
	HandleRotation(DeltaTime);

}

void ABadAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* MyController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (MyController->MoveAction)
			{
				EnhancedInput->BindAction(
					MyController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ABadAircraft::Move
				);
				EnhancedInput->BindAction(
					MyController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&ABadAircraft::Move
				);
			}

			if (MyController->LookAction)
			{
				EnhancedInput->BindAction(
					MyController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ABadAircraft::Look
				);
				EnhancedInput->BindAction(
					MyController->LookAction,
					ETriggerEvent::Completed,
					this,
					&ABadAircraft::Look
				);
			}
		}
	}
}

void ABadAircraft::Move(const FInputActionValue& Value)
{
	const FVector Axis3D = Value.Get<FVector>();

	ForwardInput = Axis3D.X;
	RightInput = Axis3D.Y;
	UpInput = Axis3D.Z;
}

void ABadAircraft::Look(const FInputActionValue& Value)
{
	const FVector Axis3D = Value.Get<FVector>();

	RotationRate.Roll = Axis3D.X * RollSpeed;
	RotationRate.Pitch = -(Axis3D.Y) * PitchSpeed;
	RotationRate.Yaw = Axis3D.Z * YawSpeed;
}

void ABadAircraft::HandleMovement(float DeltaTime)
{
	const bool bInAir = !bIsGrounded;
	const float ActualMaxSpeed = bInAir ? (MaxSpeed * 0.5f) : MaxSpeed;
	const float ActualAcceleration = bInAir ? (Acceleration * 0.5f) : Acceleration;
	const float ActualDeceleration = bInAir ? (Deceleration * 0.5f) : Deceleration;

	if (!bIsGrounded)
	{
		Velocity.Z += GravityZ * DeltaTime;
	}

	FVector LocalInput(ForwardInput, RightInput, UpInput);
	if (!LocalInput.IsNearlyZero())
	{
		LocalInput.Normalize();
	}

	const FVector DesiredDirection = GetActorRotation().RotateVector(LocalInput);
	const FVector DesiredVelocity = DesiredDirection * ActualMaxSpeed;

	const bool bHasInput = !FMath::IsNearlyZero(ForwardInput) ||
		!FMath::IsNearlyZero(RightInput) ||
		!FMath::IsNearlyZero(UpInput);

	const float AccelFactor = bHasInput ? ActualAcceleration : ActualDeceleration;
	const FVector DeltaV = DesiredVelocity - Velocity;
	if (!DeltaV.IsNearlyZero())
	{
		const FVector AccelDir = DeltaV.GetSafeNormal();
		Velocity += (AccelDir * AccelFactor * DeltaTime);
	}

	const float CurrentSpeedXY = FVector(Velocity.X, Velocity.Y, 0.f).Size();
	if (CurrentSpeedXY > ActualMaxSpeed)
	{
		const float RatioXY = ActualMaxSpeed / CurrentSpeedXY;
		Velocity.X *= RatioXY;
		Velocity.Y *= RatioXY;
	}

	const float CurrentSpeedZ = FMath::Abs(Velocity.Z);
	if (CurrentSpeedZ > ActualMaxSpeed)
	{
		const float RatioZ = ActualMaxSpeed / CurrentSpeedZ;
		Velocity.Z *= RatioZ;
	}

	const float Speed = Velocity.Size();
	const float CurrentFriction = bIsGrounded ? GroundFriction : AirFriction;
	if (Speed > KINDA_SMALL_NUMBER)
	{
		const float Drop = Speed * CurrentFriction * DeltaTime;
		const float NewSpeed = FMath::Max(Speed - Drop, 0.f);
		Velocity *= (NewSpeed / Speed);
	}

	const FVector DeltaMove = Velocity * DeltaTime;
	FHitResult Hit;
	AddActorWorldOffset(DeltaMove, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		CheckGround(Hit);
	}
	else
	{
		bIsGrounded = false;
	}

	if (bIsGrounded && Velocity.Z < 0.f)
	{
		Velocity.Z = 0.f;
	}
	
}

void ABadAircraft::HandleRotation(float DeltaTime)
{
	FRotator CurrentRot = GetActorRotation();
	CurrentRot.Roll += RotationRate.Roll * DeltaTime;
	CurrentRot.Pitch += RotationRate.Pitch * DeltaTime;
	CurrentRot.Yaw += RotationRate.Yaw * DeltaTime;

	CurrentRot.Pitch = FMath::Clamp(CurrentRot.Pitch, -MaxPitch, MaxPitch);
	CurrentRot.Roll = FMath::Clamp(CurrentRot.Roll, -MaxRoll, MaxRoll);

	SetActorRotation(CurrentRot);
}

void ABadAircraft::CheckGround(const FHitResult& Hit)
{
	bIsGrounded = (Hit.Normal.Z > 0.7f);
}
