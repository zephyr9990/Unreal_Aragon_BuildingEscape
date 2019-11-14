// Copyright Rodel Aragon 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	bool DrawDebug = false;

	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// Release what's been grabbed.
	void Release();

	// Find (assumed) attached PhysicsHandleComponent
	void FindPhysicsHandleComponent();

	// Sets (assumed) attached InputComponent
	void SetupInputComponent();

	// Return hit for first physics body in reach.
	FHitResult GetFirstPhysicsBodyInReach();

	// Returns current start of reach line.
	FVector GetReachLineStart();

	// Returns current end of reach line.
	FVector GetReachLineEnd();

	// Draw a debug line showing player's reach.
	void DrawLine();
};
