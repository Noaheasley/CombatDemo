// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "True"))
		class UAnimMontage* MeleeAttackMontage;
private:
	void AttackStart();
	void AttackEnd();

	UFUNCTION()
		void SpawnObject(FVector Lov, FRotator Rot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	bool IsMovingX = false;
	bool IsMovingY = false;

};
