#include "A2.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"

AA2::AA2()
{
	SpeedX = 200.0f;
	MaxX = 300.0f;
	MinX = -300.0f;

	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	///Script/Engine.StaticMesh'/Game/Resources/Props/Floor_400x400.Floor_400x400'
	///Script/Engine.MaterialInstanceConstant'/Game/Resources/Materials/M_Gem_A.M_Gem_A'

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

}

void AA2::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0.0f, 0.0f, 80.0f));
	SetActorScale3D(FVector(0.2f, 0.2f, 0.4f));

	HideActor();



}

void AA2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.X += SpeedX * DeltaTime;

	if (CurrentLocation.X >= MaxX)
	{
		CurrentLocation.X = MaxX;
		SpeedX = -FMath::Abs(SpeedX);
	}

	if (CurrentLocation.X <= MinX)
	{
		CurrentLocation.X = MinX;
		SpeedX = FMath::Abs(SpeedX);
	}

	SetActorLocation(CurrentLocation);

}

void AA2::HideActor()
{
	SetActorHiddenInGame(true);

	GetWorldTimerManager().SetTimer(
		ActorTimerHandle,
		this,
		&AA2::ShowActor,
		3.0f,
		false
		);
}
\
void AA2::ShowActor()
{
	SetActorHiddenInGame(false);

	GetWorldTimerManager().SetTimer(
		ActorTimerHandle,
		this,
		&AA2::HideActor,
		3.0f,
		false
	);
}

void AA2::ChangeColor()
{
	if (StaticMeshComp)
	{
		UMaterialInstanceDynamic* DynMaterial = StaticMeshComp->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMaterial)
		{
			const FLinearColor RandomColor = FLinearColor::MakeRandomColor();
			DynMaterial->SetVectorParameterValue(TEXT("Color"), RandomColor);
		}
	}
}