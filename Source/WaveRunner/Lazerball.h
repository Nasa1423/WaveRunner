// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperCharacter.h"

//#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Lazerball.generated.h"
 

UCLASS(config = Game)
class WAVERUNNER_API ALazerball : public APaperFlipbookActor
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
USphereComponent* CollisionComponent;
	protected:
	// Fireball animation
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ProjectileAnimation;
	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;
	
	void FireInDirection(const FVector& ShootDirection);

public:
	ALazerball();
	ALazerball(bool isRight);


};
