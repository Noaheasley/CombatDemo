// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	//gets the owner of the health component
	AActor* Owner = GetOwner();
	if (Owner)
	{
		//deals damage to the actor
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	//ignores if the damage is less than or equal to 0
	if (Damage <= 0)
		return;
	//clamps the health
	DefaultHealth = FMath::Clamp(DefaultHealth - Damage, 0.0f, DefaultHealth);
	//checks if the health gets lower than 0
	if (DefaultHealth <= 0)
	{
		DefaultHealth = 0;
	}
}

