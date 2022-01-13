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

	UPROPERTY(VisibleDefaultsOnly, Category = "HitBox")
	UStaticMeshComponent* TestMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillTime")
		float Killtime = 0.5f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
