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

	CollectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	CollectionRange->AttachTo(RootComponent);
	CollectionRange->SetSphereRadius(100.0f);

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
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FRotator rotation = Hitbox->GetOwner()->GetActorRotation();
	WeaponOffset.Set(100.0f, 0.0f, 0.0f);
	FVector forward = Hitbox->GetOwner()->GetActorLocation() + FTransform(rotation).TransformVector(WeaponOffset);
	DisableInput(PlayerController);
	
	SpawnObject(forward, rotation);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATestCharacter::AttackCoolDown, 1.0f, true, AttackTime);

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
	if (GetWorldTimerManager().GetTimerRemaining(AttackTimerHandle) <= 0)
	{
		EnableInput(PlayerController);
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	}
}


void ATestCharacter::SpawnObject(FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(HitboxSpawn, Loc, Rot, SpawnParams);
	WeaponHitboxRotation = WeaponRotationArray[IndexLimit];
	FRotator SpawnedActorRotation = { FRotator(0.f, Rot.Yaw, WeaponHitboxRotation) };

	WeaponHitboxSize = WeaponSizeArray[IndexLimit];
	++IndexLimit;
	if (IndexLimit == WeaponRotationArray.Num() || IndexLimit == WeaponSizeArray.Num())
		IndexLimit = 0;
	SpawnedActorRef->SetActorScale3D(WeaponHitboxSize);
	SpawnedActorRef->SetActorRotation(SpawnedActorRotation);
	MeleeHitbox = SpawnedActorRef;
}



