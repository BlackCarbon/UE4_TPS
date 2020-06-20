// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TPS_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void MoveForward(float Val);

	void MoveRight(float Val);

	void BeginCrouch();

	void EndCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent * CameraComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent * SpringArmComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
