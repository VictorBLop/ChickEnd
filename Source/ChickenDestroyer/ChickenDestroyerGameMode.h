// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChickenDestroyerGameMode.generated.h"

UCLASS(minimalapi)
class AChickenDestroyerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AChickenDestroyerGameMode();

	void SpawnHumans();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Humans")
	int32 NumberOfHumans = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float MapRadius = 15000.0;

	TArray<ACharacter*> THumansArray;

	UPROPERTY(EditDefaultsOnly, Category = "Puppy Objects")
	TSubclassOf<ACharacter> HumansClass;

};


