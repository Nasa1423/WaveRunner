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
    /**
    * Default tick function
    *
    * \param float DeltaSeconds Defines how much seconds does tick take
    */
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    /**
    * Function to change state of timeline
    *
    * \param float value Variable to set timeline state (0 is start and 1 is end)
    */
		void ProcessMovementTimeline(float value);

	UFUNCTION()
    /**
    * Event that will be executed on timeline movement end
    *
    */
		void OnEndMovementTimeline();

	UFUNCTION()
    /**
    * Event that will be executed when we step on our TriggerComponent
    *
    */
		void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
    /**
    * Event that will be executed when we leave our TriggerComponent
    *
    */
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
    /**
    * Old function to test TriggerComponentOverlap
    *
    */
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FTimeline MovementTimeline;
};