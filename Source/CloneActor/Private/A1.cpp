#include "A1.h"

AA1::AA1()
{
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 1080.0f;
	SpeedZ = 160.0f;
	MaxHeight = 160.0f;
	MinHeight = 110.0f;
	Gravity = -200.0f;
	InitialSpeedZ = 160.0f;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	///Script/Engine.StaticMesh'/Game/Resources/Props/SM_Coin_A.SM_Coin_A' ����
	///Script/Engine.MaterialInstanceConstant'/Game/Resources/Materials/M_Star.M_Star'

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Coin_A.SM_Coin_A"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Star.M_Star"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

void AA1::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(40.0f, 40.0f, 110.0f));
	SetActorScale3D(FVector(0.5f));
}

void AA1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

		//Speed���� Gravity * DeltaTime ��ŭ ���� -> �ӵ��� ���� �������ٰ� �ݴ�� �ۿ� (�Ʒ� ���� ����)
		SpeedZ += Gravity * DeltaTime;

		//���� ��ġ ��������
		FVector CurrentLocation = GetActorLocation();
		//Z�� ��ġ�� �ӵ�(SpeedZ)�� ���� ����
		CurrentLocation.Z += SpeedZ * DeltaTime;

			if (CurrentLocation.Z >= MaxHeight)
			{
				CurrentLocation.Z = MaxHeight;
				SpeedZ = -FMath::Abs(SpeedZ);
			}

			if (CurrentLocation.Z <= MinHeight)
			{
				CurrentLocation.Z = MinHeight;
				SpeedZ = InitialSpeedZ;
			}

			SetActorLocation(CurrentLocation);

	}
}
