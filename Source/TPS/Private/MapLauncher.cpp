// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLauncher.h"

//#include<vector>
//using namespace std;

std::vector<UClass>brickList;
// Sets default values for this component's properties
UMapLauncher::UMapLauncher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMapLauncher::BeginPlay()
{
	Super::BeginPlay();

	// ...
	 
}


// Called every frame
void UMapLauncher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

