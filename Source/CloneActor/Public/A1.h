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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yaw")
	float SpeedZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yaw")
	float MaxHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yaw")
	float MinHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yaw")
	float Gravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yaw")
	float InitialSpeedZ;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
