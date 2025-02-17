#pragma once

// FString, TArray, 매크로UE_LOG등 각종 유틸 함수들이 정의되어 있다. 
#include "CoreMinimal.h"

// AActor를 상속 받기 위해 필요한 헤더 파일.
#include "GameFramework/Actor.h"

// 리플렉션 시스템에 필요한 코드를 자동 생성하기 위한 매크로.
#include "A1.generated.h"

UCLASS()
class CLONEACTOR_API AA1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// 생성자
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
