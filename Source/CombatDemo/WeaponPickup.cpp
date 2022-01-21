// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	active = true;
	//sets the mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//sets the mesh to the root
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponPickup::Interacted()
{
	//deactivates and destroies the object
	active = false;
	Destroy(true);
}

bool AWeaponPickup::GetActive()
{
	return active;
}

float AWeaponPickup::IncreaseDamage(float Damage)
{
	//increases damage
	Damage += DamageMod;
	return Damage;
}

