// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChickenDestroyerGameMode.h"
#include "ChickenDestroyerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HumanAIController.h"


//#include "CatchDogGameMode.h"
//#include "CatchDogCharacter.h"
#include "UObject/ConstructorHelpers.h"
//#include "CatchDogGameState.h"


AChickenDestroyerGameMode::AChickenDestroyerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AChickenDestroyerGameMode::SpawnHumans()
{
	if (HasAuthority())
	{
		// Spawn Puppies!
		for (int i = 0; i < NumberOfHumans; i++)
		{
			// Spawn actor
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (HumansClass)
			{
				FVector Origin = FVector(4780.0f, 3030.0f, 150.0f); // Center of the map (aprox)

				FVector RandomLocation = Origin;

				//// Create and assign the AIController to the Puppy
				if (GetWorld())
				{
					AHumanAIController* HumanAIController = GetWorld()->SpawnActor<AHumanAIController>(AHumanAIController::StaticClass(), FVector::ZeroVector, FRotator(0.0f, 0.0f, 0.0f));

					if (HumanAIController)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HumanAIController is good"), true, true, FLinearColor::Green, 5.0f);
						
						RandomLocation = HumanAIController->GetRandomPointInRadiusWithOrigin(Origin, MapRadius); // Generate reachable random point with AIController
					
						RandomLocation.Z += 3000.0f;
					}

					// Spawn Puppy in position received previously
					ACharacter* HumanActor = GetWorld()->SpawnActor<ACharacter>(
						HumansClass,
						RandomLocation,
						FRotator(0.0f, 0.0f, 0.0f),
						SpawnInfo);

					if (HumanActor)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HumanActor is good"), true, true, FLinearColor::Green, 5.0f);

						// Check if the AIController was successfully spawned
						if (HumanAIController)
						{
							// Possess the Puppy with the AIController
							HumanAIController->Possess(HumanActor);
						}

						// Activate the movement component
						HumanActor->GetCharacterMovement()->Activate();

						THumansArray.Add(HumanActor);
					}
				}

			}

		}
	}
}