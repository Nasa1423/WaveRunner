// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class WAVERUNNER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
		void ProcessMovementTimeline(float Value);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
		USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TriggerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spline")
		UCurveFloat* MovementCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
		bool bAutoActivate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", meta = (EditCondition = "!bRestartOnEndTimeline"))
		bool bReverseOnEndTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", meta = (EditCondition = "!bReverseOnEndTimeline"))
		bool bRestartOnEndTimeline;

private:
	FTimeline MovementTimeline;

};
