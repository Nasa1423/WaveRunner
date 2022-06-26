// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{	

	//requestedHeight = 0;
	//speed = 0;
	//bIsMoving = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline__"));
	SplineComponent->SetupAttachment(GetRootComponent());

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY_FUCKING_SPIKE"));
	MeshComponent->SetupAttachment(SplineComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(MeshComponent);
	//TriggerBox->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	//TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	//TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	//TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);
	
	//StartTime = 0;

}
void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Simple message"));

}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::TriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::TriggerEndOverlap);
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}

	//float CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;

	//Reach the end
	//if (CurrentSplineTime >= 1.0f) {
		//if (bSplineInLoop) {
			//bCanMoveActor = true;

			//StartTime = GetWorld()->GetTimeSeconds();

			//CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;
		//}
	//}
}

void ASpikeTrap::ProcessMovementTimeline(float value)
{
	const float SplineLength = SplineComponent->GetSplineLength();

	const FVector CurrentSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(value * SplineLength, ESplineCoordinateSpace::World);

	CurrentSplineRotation.Pitch = 0.f;
	//MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, FRotator(0.0f, 0.0f, 0.0f));
}

void ASpikeTrap::OnEndMovementTimeline()
{
	
}

void ASpikeTrap::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);
	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	MovementTimeline.Play();
}

void ASpikeTrap::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
