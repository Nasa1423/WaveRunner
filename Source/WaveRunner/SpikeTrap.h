// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "SpikeTrap.generated.h"

UCLASS()
class WAVERUNNER_API ASpikeTrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpikeTrap();

private:
	//FVector CurrentLocation;
	//float speed;
	//bool bIsMoving;
	//float requestedHeight;
	//UPROPERTY(EditAnywhere, Category = "Custom")
		//double LinearSpeed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* ExampleTimelineComp;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		float TotalPathTimeController;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		bool bSplineInLoop;

	bool bCanMoveActor;

	float StartTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ProcessMovementTimeline(float value);

	UFUNCTION()
		void OnEndMovementTimeline();

	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(VisibleAnywhere)
		USplineComponent* SplineComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
		UCurveFloat* MovementCurve;
	

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FTimeline MovementTimeline;
};