#pragma once

// FString, TArray, ��ũ��UE_LOG�� ���� ��ƿ �Լ����� ���ǵǾ� �ִ�. 
#include "CoreMinimal.h"

// AActor�� ��� �ޱ� ���� �ʿ��� ��� ����.
#include "GameFramework/Actor.h"

// ���÷��� �ý��ۿ� �ʿ��� �ڵ带 �ڵ� �����ϱ� ���� ��ũ��.
#include "A1.generated.h"

UCLASS()
class CLONEACTOR_API AA1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// ������
	AA1();


protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	float RotationSpeed;
	float SpeedZ;
	float MaxHeight;
	float MinHeight;
	float Gravity;
	float Bounciness;
	float InitialSpeedZ;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
