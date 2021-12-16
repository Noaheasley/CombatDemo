// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, 90.0f),
		FRotator(-10.0, 0.0f, 0.0f)
	);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//attck
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATestCharacter::AttackStart);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ATestCharacter::AttackEnd);
}

void ATestCharacter::MoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector forward = rotator.Vector();
	AddMovementInput(forward, AxisValue);

	IsMovingX = AxisValue != 0.0f;
	bUseControllerRotationYaw = IsMovingX || IsMovingY;
}

void ATestCharacter::MoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector right = FVector::CrossProduct(FVector::UpVector, rotator.Vector());
	AddMovementInput(right, AxisValue);

	IsMovingY = AxisValue != 0.0f;
	bUseControllerRotationYaw = IsMovingX || IsMovingY;
}

void ATestCharacter::AttackStart()
{
}

void ATestCharacter::AttackEnd()
{

}


