// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Lazerball.h"
#include "WaveRunnerCharacter.generated.h"

class UTextRenderComponent;

/**
 * This class is the default character for WaveRunner, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class AWaveRunnerCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
    /**
     * Default tick function
     *
     * \param float DeltaSeconds Defines how much seconds does tick take
     */
	virtual void Tick(float DeltaSeconds) override;
protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DeathAnimation;
	
	// The animation to attack (shot lazers)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* AttackAnimation;

	//UPROPERTY(EditAnywhere, Category = Projectile)
	//TSubclassOf<class ALazerball> Lazerball;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//FVector MuzzleOffset;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

    /**
     * Function to move the character
     *
     * \param float Value Defines the speed of the character
     */
	void MoveRight(float Value);

    /**
     * Function to launch projectile
     *
     */
	void Lazershot();

    /**
     * Function to control animation
     *
     */
	void UpdateCharacter();

	UFUNCTION()
    /**
     * Function to kill character
     *
     */
	void Suicide();

    /**
     * Function to initialize APawn interface
     *
     */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	AWaveRunnerCharacter();


	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
