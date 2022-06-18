// Fill out your copyright notice in the Description page of Project Settings.

#include "Lazerball.h"
#include "PaperSpriteComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

ALazerball::ALazerball()
{
    PrimaryActorTick.bCanEverTick = true;
    if (!RootComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }
    //GetSprite()->SetFlipbook(ProjectileAnimation);
    if (!ProjectileMovementComponent)
    {
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 750.0f;
        ProjectileMovementComponent->MaxSpeed = 1000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

};

void ALazerball::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void ALazerball::BeginPlay()
{
    Super::BeginPlay();

}

void ALazerball::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
