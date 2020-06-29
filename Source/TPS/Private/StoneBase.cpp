// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneBase.h"

// Sets default values
AStoneBase::AStoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoneBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStoneBase* AStoneBase::CreateStone(FIntVector pos) {
	return nullptr;
}
