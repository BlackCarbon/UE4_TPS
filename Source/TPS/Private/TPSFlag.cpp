// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSFlag.h"
#include "Components/BoxComponent.h"

// Sets default values
ATPSFlag::ATPSFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FLAG"));

	flagteam = 0;
}

// Called when the game starts or when spawned
void ATPSFlag::BeginPlay()
{
	Super::BeginPlay();
	
}


