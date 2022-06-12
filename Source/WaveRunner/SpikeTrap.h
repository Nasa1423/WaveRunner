// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"
#include "SpikeTrap.generated.h"

UCLASS()
class WAVERUNNER_API ASpikeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpikeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SpikeMesh;
	UPROPERTY(VisibleAnywhere)
		USplineComponent* SplineComponent;
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* TriggerBox;
	UFUNCTION()
		int callback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
