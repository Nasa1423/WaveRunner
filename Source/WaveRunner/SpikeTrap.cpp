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
	SplineComponent->SetupAttachment(RootComponent);
	SpikeMesh->SetupAttachment(SplineComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);


}
void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Simple message"));
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

