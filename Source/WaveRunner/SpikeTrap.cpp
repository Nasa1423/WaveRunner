// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
//#include ""

// Sets default values
ASpikeTrap::ASpikeTrap()
{	

	requestedHeight = 0;
	speed = 0;
	bIsMoving = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY_FUCKING_SPIKE"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE_BLYAT"));
	//SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	SplineComponent->Duration = TotalPathTimeController;
	SpikeMesh->SetupAttachment(SplineComponent);

	CurrentLocation = SpikeMesh->GetComponentLocation();

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	TriggerBox->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	//TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);
	
	StartTime = 0;


	//ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	//MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);
	//FOnTimelineEvent OnTimelineFinishedFunction;
	//OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	//MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);
	//MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	//if (bAutoActivate)
	//{
	//	MovementTimeline.PlayFromStart();
	//}

}
void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Simple message"));
	//moveUp(500);
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::TriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::TriggerEndOverlap);

	StartTime = GetWorld()->GetTimeSeconds();
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsMoving) {
		if (requestedHeight - CurrentLocation.Z >= speed) {
			CurrentLocation.Z += speed;
		}
		else {
			CurrentLocation.Z = requestedHeight;
		}
		SpikeMesh->SetWorldLocation(CurrentLocation);
		if (CurrentLocation.Z == requestedHeight) {
			bIsMoving = false;
		}
	}

	float CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;

	float Distance = SplineComponent->GetSplineLength() * CurrentSplineTime;

	// World position 

	FVector Position = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	SpikeMesh->SetRelativeLocation(Position);

	// World Rotation 
	FVector Direction = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	// Create rotator
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();
	SpikeMesh->SetRelativeRotation(Rotator);

	//Reach the end
	if (CurrentSplineTime >= 1.0f) {
		if (bSplineInLoop) {
			bCanMoveActor = true;

			StartTime = GetWorld()->GetTimeSeconds();

			CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;
		}
	}
}

void ASpikeTrap::ProcessMovementTimeline() {

}

void ASpikeTrap::OnEndMovementTimeline() {

}

void ASpikeTrap::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);
}

void ASpikeTrap::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}

//void ASpikeTrap::moveUp(float points) {
	//bIsMoving = true;
	//requestedHeight = CurrentLocation.Z + points;
	//speed = 150.0f;
//}
