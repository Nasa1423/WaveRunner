// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY_FUCKING_SPIKE"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE_BLYAT"));
	SplineComponent->SetupAttachment(RootComponent);
	SpikeMesh->SetupAttachment(SplineComponent);

	TriggerBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerBox->InitCapsuleSize(55.f, 96.0f);;
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::callback);


}
int ASpikeTrap::callback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

