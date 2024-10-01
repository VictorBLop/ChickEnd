// Fill out your copyright notice in the Description page of Project Settings.


#include "ChickenDestroyerGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "ChickenDestroyerGameMode.h"
#include "ChickenDestroyerPlayerController.h"

void AChickenDestroyerGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

void AChickenDestroyerGameStateBase::StartPreGame()
{
	GetWorld()->GetTimerManager().ClearTimer(GameTimer);
	GetWorld()->GetTimerManager().ClearTimer(StartTimer);

	
	OnTimerUpdate.Broadcast((int)GameTime / 60, (int)GameTime % 60, (int)GameTime);

	// Start Game Timer
	GetWorld()->GetTimerManager().SetTimer(
		StartTimer, // handle to cancel timer at a later time
		this, // the owning object
		&AChickenDestroyerGameStateBase::StartGame, // function to call on elapsed
		TimeToStartGame, // float delay until elapsed
		false); // looping

	// Game Mode
	if (AChickenDestroyerGameMode* ChickenDestroyerGameMode = Cast<AChickenDestroyerGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ChickenDestroyerGameMode->SpawnHumans();
	}

	// Player Controller
	ChickenDestroyerPlayerController = Cast<AChickenDestroyerPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (ChickenDestroyerPlayerController)
	{
		ChickenDestroyerPlayerController->SetIgnoreMoveInput(true);
		ChickenDestroyerPlayerController->SetIgnoreLookInput(true);
	}
}

void AChickenDestroyerGameStateBase::StartGame()
{
	// Start Game Timer
	GetWorld()->GetTimerManager().SetTimer(
		GameTimer, // handle to cancel timer at a later time
		this, // the owning object
		&AChickenDestroyerGameStateBase::Endgame, // function to call on elapsed
		GameTime, // float delay until elapsed
		false); // looping

	// Start Game Timer
	GetWorld()->GetTimerManager().SetTimer(
		StartTimer, // handle to cancel timer at a later time
		this, // the owning object
		&AChickenDestroyerGameStateBase::UpdateTimer, // function to call on elapsed
		1.0f, // float delay until elapsed
		true); // looping

	// Player Controller (enable input)
	if (ChickenDestroyerPlayerController)
	{
		ChickenDestroyerPlayerController->SetIgnoreMoveInput(false);
		ChickenDestroyerPlayerController->SetIgnoreLookInput(false);
	}

}

void AChickenDestroyerGameStateBase::UpdateTimer()
{
	// Game Timer
	
	if (HasAuthority())
	{
		
		Seconds = GetWorld()->GetTimerManager().GetTimerRemaining(GameTimer);

		if (Seconds >= 0)
		{
			OnTimerUpdate.Broadcast(Seconds / 60, Seconds % 60, Seconds); // Broadcast event Update Timer

			//OnRep_GameTimer();
		}
	}
}

void AChickenDestroyerGameStateBase::Endgame()
{
	// Do stuff when game ends
}
