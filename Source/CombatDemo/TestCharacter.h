// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "WeaponPickup.h"
#include "HitBox.h"
#include "TestCharacter.generated.h"


UCLASS()
class COMBATDEMO_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Moves the player forward
	UFUNCTION(BlueprintCallable)
		void MoveForward(float AxisValue);
	//Moves the player Right
	UFUNCTION(BlueprintCallable)
		void MoveRight(float AxisValue);
	
public:
	//Array for the Weapon Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<float> WeaponRotationArray;
	//Array for the Weapon size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FVector> WeaponSizeArray;
	//reference for the Hitbox
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> HitboxSpawn;
	//the spawn location of the weapon hitbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector WeaponOffset;
	//time during a attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackTime = 0;

protected:
	//size of the weapon hitbox
	UPROPERTY()
		FVector WeaponHitboxSize;
	//roation of the weapon hitbox on the roll
	UPROPERTY()
		float WeaponHitboxRotation;
private:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UActorComponent* Hitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AHitBox* WeaponHitboxRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "True"))
	class UAnimMontage* MeleeAttackMontage;
	//limit for the arrays
	int IndexLimit = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AHitbox* WeaponHitbox;
	//bool to see if the actor is attacking
	bool isAttcking = false;
	//timer handle for the Attack time
	FTimerHandle AttackTimerHandle;

	

private:
	//makes the player attack by spawning a hitbox in front of them
	void AttackStart();
	//allows the player to pick up items
	void Interact();
	//cool down in between player attacks
	void AttackCoolDown();
	//range the player can be placed
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
		USphereComponent* CollectionRange;
	//weapon the player is holding
	UPROPERTY(EditAnywhere, Category = "Pickup")
		UActorComponent* Wielded;
	//spawns a hitbox
	UFUNCTION()
		void SpawnObject(FVector Lov, FRotator Rot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	bool IsMovingX = false;
	bool IsMovingY = false;

};
