#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

class ASpawnVolume;
class ACoinItem;
class ASpartaPlayerController;
class USpartaGameInstance;

UCLASS()
class CLONEACTOR_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> CoinsToSpawnPerWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;

	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();
	
	void StartLevel();
	void EndLevel();
	void StartWave();
	void EndWave();
	void OnWaveTimeUp();
	void OnCoinCollected();
	void UpdateHUD();

private:
	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	ASpawnVolume* GetSpawnVolume() const;
	ASpartaPlayerController* GetSpartaPlayerController() const;
	USpartaGameInstance* GetSpartaGameInstance() const;

};
