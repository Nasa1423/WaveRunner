// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY_FUCKING_SPIKE"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE_BLYAT"));
	//SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	SplineComponent->Duration = TotalPathTimeController;
	SpikeMesh->SetupAttachment(SplineComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	TriggerBox->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	//TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);

	StartTime = 0;


}
void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Simple message"));
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	StartTime = GetWorld()->GetTimeSeconds();
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

