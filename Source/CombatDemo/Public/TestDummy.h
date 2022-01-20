// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestDummy.generated.h"

UCLASS()
class COMBATDEMO_API ATestDummy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		AActor* DamageHitBox;

private:
	float defualtHealth;
};
