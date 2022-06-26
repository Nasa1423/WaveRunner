// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(GetRootComponent());

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(SplineComponent);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::TriggerBeginOverlap);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AMovingPlatform::TriggerEndOverlap);

	const FVector SplineLocation = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	MeshComponent->SetWorldLocation(SplineLocation);

	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);

	if (bAutoActivate)
	{
		MovementTimeline.PlayFromStart();
	}
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}

}

void AMovingPlatform::ProcessMovementTimeline(float Value)
{
	const float SplineLength = SplineComponent->GetSplineLength();

	FVector CurrentSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
	CurrentSplineRotation.Pitch = 0.f;
	//MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, FRotator(0.0f, 0.0f, 0.0f));
}

void AMovingPlatform::OnEndMovementTimeline()
{
	if (bReverseOnEndTimeline)
	{
		MovementTimeline.Reverse();
	}
	else if (bRestartOnEndTimeline)
	{
		MovementTimeline.PlayFromStart();
	}
}

void AMovingPlatform::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	MovementTimeline.PlayFromStart();
}

void AMovingPlatform::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!MovementTimeline.IsReversing())
	{
		MovementTimeline.Reverse();
	}
}