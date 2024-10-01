// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ChickenDestroyerGameStateBase.generated.h"

class AChickenDestroyerPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTimerUpdate, int32, Minutes, int32, Seconds, int32, SecondsForSound);

/**
 * 
 */
UCLASS()
class CHICKENDESTROYER_API AChickenDestroyerGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void StartPreGame();

protected:

	virtual void BeginPlay() override;

	void StartGame();

	void UpdateTimer();

	void Endgame();

	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdate OnTimerUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToStartGame = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameTime = 60.0f;

	UPROPERTY(BlueprintReadOnly)
	int32 Seconds = 0.0f;

private:

	AChickenDestroyerPlayerController* ChickenDestroyerPlayerController = nullptr;

	FTimerHandle GameTimer;

	FTimerHandle StartTimer;
	
};
