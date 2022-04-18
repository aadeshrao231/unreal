// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle = InitialYaw + OpenAngle;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s HAve opendoor script but pressure plat has not been set"), *GetOwner()->GetName());
	}
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenTheDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseTheDoor(DeltaTime);
		}	
	}	
}


void UOpenDoor::OpenTheDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Current rotation: %s"),*GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("CurrentYaw Rotation: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorOpen = GetOwner()->GetActorRotation();
	DoorOpen.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorOpen);
}


void UOpenDoor::CloseTheDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Current rotation: %s"),*GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("CurrentYaw Rotation: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorOpen = GetOwner()->GetActorRotation();
	DoorOpen.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorOpen);
}