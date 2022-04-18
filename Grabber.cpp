// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("HHEyy how are you"))
	FindPhysicHandle();
	SettingUpGrabberInputComponent();
}


void UGrabber::FindPhysicHandle()
{
	//Checking For Physic Handle Component
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicHandle)
	{
		// Physic Handle Found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physic Handle Component not found in: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SettingUpGrabberInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component found in: %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not found in: %s"), *GetOwner()->GetName());
	} 	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed"));
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector()* Reach;

	FHitResult HitResult = GetFirstPhysicBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor())
	{
		//To attach physic handle
		PhysicHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEndPoint
		);
	}
		
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released"));

	PhysicHandle->ReleaseComponent();
}

	
	
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector()* Reach;

	// if the physic handle is attach

	if (PhysicHandle->GrabbedComponent)
	{
		PhysicHandle->SetTargetLocation(LineTraceEndPoint);
	}
	
}

FHitResult UGrabber::GetFirstPhysicBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// UE_LOG(LogTemp, Warning, TEXT("View Location: %s\nView Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());


	FVector LineTraceEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector()* Reach;

	

	FHitResult Hit;
	FCollisionQueryParams TraceParms(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParms
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("THe obeject you hit is: %s"), *(ActorHit->GetName()));

	}
	return Hit;
}

// void UGrabber::DebuggingLine()
// {

// 	DrawDebugLine
// 	(
// 		GetWorld(),
// 		PlayerViewPointLocation,
// 		LineTraceEndPoint,
// 		FColor(0, 255, 0),
// 		false,
// 		0.f,
// 		0,
// 		5.f
// 	);
// }