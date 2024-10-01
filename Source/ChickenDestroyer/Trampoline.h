// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trampoline.generated.h"

class UBoxComponent;

UCLASS()
class CHICKENDESTROYER_API ATrampoline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrampoline();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ActorMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampoline")
	float LaunchPower = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampoline")
	bool LaunchOverrideXYAxis = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampoline")
	bool LaunchOverrideZAxis = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
