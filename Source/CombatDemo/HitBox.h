// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitBox.generated.h"

UCLASS()
class COMBATDEMO_API AHitBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBox();
	//mesh of the hitbox
	UPROPERTY(VisibleDefaultsOnly, Category = "HitBox")
	UStaticMeshComponent* TestMeshComponent;
	//Time it takes till the Hitbox is destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillTime")
		float Killtime = 0.5f;
	//ammount of damage the hitbox deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillTime")
		float Damage = 0.5f;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
