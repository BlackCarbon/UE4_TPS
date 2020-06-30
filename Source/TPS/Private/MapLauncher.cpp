// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLauncher.h"
#include "StoneBase.h"
#include "BlueprintGraphClasses.h"
//#include "MapProductor.h"

// Sets default values for this component's properties
UMapLauncher::UMapLauncher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	instance = this;
	// ...
}


// Called when the game starts
void UMapLauncher::BeginPlay()
{
	Super::BeginPlay();
	InitializeMap();
	// ...

	 
}

// Called every frame
void UMapLauncher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMapLauncher::InitializeMap() {
	vector<vector<int>>map = MapProductor(BlockSize,MapSize).getMap(1349880437);
	//PositionTranslator trans(StoneScale);
	for (int i = 0;i < map.size();i++) {
		for (int j = 0;j < map[i].size();j++) {
			for (int k = 0;k <= map[i][j];k++) {
				UE_LOG(LogTemp, Log, TEXT("Product Stone"));
			/*	FVector p = PositionTranslator::transFromDispersedToContinuous(FIntVector{
					i, j, k
				});
				
				FTransform spawnTransform;
				spawnTransform.SetLocation(transFromDispersedToContinuous(FIntVector(i, j, k)));
			//	ConstructorHelpers::FClassFinder<AStoneBase> BPClass(TEXT("/Game/Blueprints"));
				FActorSpawnParameters spawn;
				ConstructorHelpers::FClassFinder<AStoneBase> BPClass(TEXT("/Game/Blueprints"));
				AStoneBase *x = GetWorld()->SpawnActor<AStoneBase>(BPClass.Class,spawnTransform, spawn);
			//	instance->GetTransform().setLocation(transFromDispersedToContinuous(FIntVector(i, j, k)));*/
			}
		}
	}
}

FVector UMapLauncher::transFromDispersedToContinuous(FIntVector p) {
	float HEIGHT=StoneScale.Z;
	float EDGEWIDTH=StoneScale.X;
	FVector ans;
	ans.Z = p.Z * HEIGHT + HEIGHT / 2.0;
	ans.Y = (p.Y - 0.5 * (p.X & 1)) * sqrt(3) * EDGEWIDTH;
	ans.X = p.X * 1.5 * EDGEWIDTH;
	return ans*50;
}

/*
template<UCLASS T>
void UMapLauncher::CreateStone<T>(FIntVector pos){

//	AActor * stone= GetWorld()->SpawnActor<AActor::StaticClass()>(Stone,pos);
	/*static ConstructorHelpers::FClassFinder<AActor> bpClass(TEXT("/Game/BluePrints/BP_stone"));
	if (bpClass.Class != NULL)
	{
		AActor *x=GetWorld()->SpawnActor(bpClass.Class);
		x->SetActorLocation(pos);
		x->SetActorScale3D(FVector(StoneScale));
	}
	StoneBase* x = GetWorld()->SpawnActor<StoneBase>(StoneBase::StaticClass);
	x->SetActorLocation(pos);
	x->SetActorScale3D(FVector(StoneScale));
}
*/


