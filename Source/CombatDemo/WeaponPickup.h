// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hitbox.h"
#include "WeaponPickup.generated.h"

UCLASS()
class COMBATDEMO_API AWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//what happens when the item is interacted
	void Interacted();

	bool GetActive();
	//modifier for the damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageMod")
		float DamageMod = 0.25;
	//function to increase damage
	UFUNCTION()
		float IncreaseDamage(float Damage);
private:
	//see if the actor is active or not
	UPROPERTY()
		bool active;
	//reference for the mesh
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* mesh;

};
