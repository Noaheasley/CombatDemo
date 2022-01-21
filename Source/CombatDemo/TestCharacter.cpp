// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//sets up the SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, 90.0f),
		FRotator(-10.0, 0.0f, 0.0f)
	);
	//sets up the Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//sets up the collection range
	CollectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	CollectionRange->AttachTo(RootComponent);
	CollectionRange->SetSphereRadius(100.0f);
	//sets up the Hitbox of the player
	Hitbox = CreateDefaultSubobject<UActorComponent>(TEXT("HitBox"));
	//load animation montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeAttackMontageObject(TEXT("AnimMontage'/Game/Character/Animation/Attack.Attack'"));
	if (MeleeAttackMontageObject.Succeeded())
	{
		MeleeAttackMontage = MeleeAttackMontageObject.Object;
	}
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (Wielded)
	{
		Wielded->GetOwner()->SetActorHiddenInGame(true);
	}
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
	//binds the actions for attack and pickup
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATestCharacter::AttackStart);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ATestCharacter::Interact);
}

void ATestCharacter::MoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector forward = rotator.Vector();
	AddMovementInput(forward, AxisValue);
	
	IsMovingX = AxisValue != 0.0f;
	bUseControllerRotationYaw = false;
}

void ATestCharacter::MoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector right = FVector::CrossProduct(FVector::UpVector, rotator.Vector());
	AddMovementInput(right, AxisValue);

	IsMovingY = AxisValue != 0.0f;
	bUseControllerRotationYaw = false;
}

void ATestCharacter::AttackStart()
{
	//gets a reference to the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//gets the rotation of the player
	FRotator rotation = Hitbox->GetOwner()->GetActorRotation();
	//sets the Weapon offset in front of the player
	WeaponOffset.Set(100.0f, 0.0f, 0.0f);
	//gets the forward facing of the player
	FVector forward = Hitbox->GetOwner()->GetActorLocation() + FTransform(rotation).TransformVector(WeaponOffset);
	//disables the input of the player
	DisableInput(PlayerController);
	//spawns a hitbox
	SpawnObject(forward, rotation);
	//sets a timer for a attack delay
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATestCharacter::AttackCoolDown, 1.0f, true, AttackTime);
	//plays a animation
	PlayAnimMontage(MeleeAttackMontage, 1.f, FName("start_1"));
}

void ATestCharacter::Interact()
{
	TArray<AActor*> inRangeItems;
	CollectionRange->GetOverlappingActors(inRangeItems);
	for (int i = 0; i < inRangeItems.Num(); i++)
	{
		AWeaponPickup* const testItem = Cast<AWeaponPickup>(inRangeItems[i]);
		if (testItem && !testItem->IsPendingKill() && testItem->GetActive())
		{
			testItem->Interacted();
			if (Wielded)
			{
				Wielded->GetOwner()->SetActorHiddenInGame(false);
			}
		}
	}
}

void ATestCharacter::AttackCoolDown()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//if the timer reaches 0 it re enables the player input
	if (GetWorldTimerManager().GetTimerRemaining(AttackTimerHandle) <= 0)
	{
		EnableInput(PlayerController);
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	}
}


void ATestCharacter::SpawnObject(FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnParams;
	//spawns the hitbox in front of the player
	AHitBox* SpawnedActorRef = GetWorld()->SpawnActor<AHitBox>(HitboxSpawn, Loc, Rot, SpawnParams);
	WeaponHitboxRef = SpawnedActorRef;
	//Sets the WeaponHitboxRotation to the WeaponRotation index
	WeaponHitboxRotation = WeaponRotationArray[IndexLimit];
	//FRotator that uses the WeaponHitboxRotation 
	FRotator SpawnedActorRotation = { FRotator(0.f, Rot.Yaw, WeaponHitboxRotation) };
	//sets the hitbox size to be the same as the hitbox in the array index
	WeaponHitboxSize = WeaponSizeArray[IndexLimit];
	//increment the index
	++IndexLimit;
	//if the index limit reaches the max array index of weapon rotation and size it'll restart the index limit
	if (IndexLimit == WeaponRotationArray.Num() || IndexLimit == WeaponSizeArray.Num())
		IndexLimit = 0;
	//sets the size and rotation
	SpawnedActorRef->SetActorScale3D(WeaponHitboxSize);
	SpawnedActorRef->SetActorRotation(SpawnedActorRotation);
}



