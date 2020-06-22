// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/TPSHealthComponent.h"
#include "..\Public\TPSCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComp = CreateDefaultSubobject<UTPSHealthComponent>(TEXT("HealthComp"));

}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	HealthComp->OnHealthChanged.AddDynamic(this, &ATPSCharacter::OnMyHealthChanged);

}

void ATPSCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector(), Val);

}

void ATPSCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector(), Val);
}

void ATPSCharacter::BeginCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Crouch!"));
	Crouch();
}

void ATPSCharacter::EndCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("End Crouch!"));
	UnCrouch();
}

void ATPSCharacter::OnMyHealthChanged(UTPSHealthComponent * MyHealthComp, float Health, float HealthDelta, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{

		bDied = true;

		GetMovementComponent()->StopMovementImmediately();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);
	}
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookDown", this, &ATPSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ATPSCharacter::AddControllerYawInput);


	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATPSCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATPSCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSCharacter::Jump);
}

