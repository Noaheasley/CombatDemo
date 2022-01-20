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

	UFUNCTION(BlueprintCallable)
		void MoveForward(float AxisValue);

	UFUNCTION(BlueprintCallable)
		void MoveRight(float AxisValue);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<float> WeaponRotationArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FVector> WeaponSizeArray;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> HitboxSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	AActor* MeleeHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector WeaponOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector WeaponHitboxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponHitboxRotation;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UActorComponent* Hitbox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "True"))
	class UAnimMontage* MeleeAttackMontage;

	int IndexLimit = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AHitbox* WeaponHitbox;

	bool isAttcking = false;
	FTimerHandle AttackTimerHandle;

	

private:
	void AttackStart();

	void Interact();

	void AttackCoolDown();

	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
		USphereComponent* CollectionRange;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		UActorComponent* Wielded;



	UFUNCTION()
		void SpawnObject(FVector Lov, FRotator Rot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	bool IsMovingX = false;
	bool IsMovingY = false;

};
