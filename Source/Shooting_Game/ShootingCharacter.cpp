// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingCharacter.h"
#include "Components/InputComponent.h"
#include "Gun.h"

// Sets default values
AShootingCharacter::AShootingCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShootingCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShootingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShootingCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForword"), this, &AShootingCharacter::MoveForward);	 // Forword-backword
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);			 // look up - down
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);			 // look right - left
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShootingCharacter::LookRightRate); // Look right - left Rate
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShootingCharacter::LookupRate);		 // Look up - down rate
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShootingCharacter::MoveRight);		 // move right - left
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShootingCharacter::Shoot);
}

float AShootingCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApplied = FMath::Min(Health, DamageToApplied);

	Health -= DamageToApplied;

	UE_LOG(LogTemp, Warning, TEXT("Health is %f:"), Health);

	return DamageToApplied;
}

void AShootingCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShootingCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShootingCharacter::LookupRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingCharacter::Shoot()
{
	Gun->PullTrigger();
}

bool AShootingCharacter::IsDead() const
{
	return Health <= 0;
}