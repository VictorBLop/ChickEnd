// Fill out your copyright notice in the Description page of Project Settings.


#include "Trampoline.h"
#include "Components/BoxComponent.h"
#include "ChickenDestroyerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATrampoline::ATrampoline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize sphere collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere Collider"));
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Enable collision for queries and physics.
	BoxCollider->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BoxCollider);

	//BoxCollider->SetSimulatePhysics(true);
	//BoxCollider->SetEnableGravity(true);
	//BoxCollider->SetCollisionResponseToAllChannels(ECR_Block); // Set collision response to block all channels.

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrampoline::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxColliderOverlap);
}

void ATrampoline::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AChickenDestroyerCharacter* ChickenDestroyerCharacter = Cast<AChickenDestroyerCharacter>(OtherActor))
	{
		ChickenDestroyerCharacter->LaunchCharacter(GetActorUpVector() * LaunchPower, LaunchOverrideXYAxis, LaunchOverrideZAxis);
	}
}

// Called every frame
void ATrampoline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

