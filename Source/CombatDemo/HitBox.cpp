// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"

// Sets default values
AHitBox::AHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!TestMeshComponent)
	{
		TestMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("testMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube1.Cube1'"));
		if (Mesh.Succeeded())
		{
			//sets the mesh to the actor
			TestMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}
	//sets the lifespan to be the killtime
	InitialLifeSpan = Killtime;
}

// Called when the game starts or when spawned
void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	//sets the lifetime
	SetLifeSpan(Killtime);
}

// Called every frame
void AHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

