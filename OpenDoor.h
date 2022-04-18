// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSPLUS_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenTheDoor(float DeltaTime);
	void CloseTheDoor(float DeltaTime);

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .3f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 5.f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

};
