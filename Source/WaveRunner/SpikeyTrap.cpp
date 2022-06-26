// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeyTrap.h"

// Sets default values
ASpikeyTrap::ASpikeyTrap()
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
void ASpikeyTrap::BeginPlay()
{
	Super::BeginPlay();

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpikeyTrap::TriggerBeginOverlap);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &ASpikeyTrap::TriggerEndOverlap);

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
void ASpikeyTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}
}

void ASpikeyTrap::ProcessMovementTimeline(float Value)
{
	const float SplineLength = SplineComponent->GetSplineLength();

	FVector CurrentSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
	CurrentSplineRotation.Pitch = 0.f;
	//MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, FRotator(0.0f, 0.0f, 0.0f));
}

void ASpikeyTrap::OnEndMovementTimeline()
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

void ASpikeyTrap::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor != this)
	MovementTimeline.PlayFromStart();
}

void ASpikeyTrap::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (!MovementTimeline.IsReversing())
	//{
	//	MovementTimeline.Reverse();
	//}
}
