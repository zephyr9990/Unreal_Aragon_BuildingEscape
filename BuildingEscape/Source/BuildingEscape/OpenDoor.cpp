// Copyright Rodel Aragon 2019


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMassOnPlate = 0.0f;
	
	// Find all the overlapping actors.
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMassOnPlate; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through overlapping actors and calculate total mass
	for (const AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressure plate."), *Actor->GetName());
		TotalMassOnPlate += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMassOnPlate;
}