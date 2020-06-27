// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLauncher.h"
//#include "MapProductor.h"

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
	auto map = MapProductor().getMap(1349880437);
	MapProductor::PositionTranslator trans;
	for (int i = 0;i < map.size();i++) {
		for (int j = 0;j < map[i].size();j++) {
			for (int k = 0;k <= map[i][j];k++) {
				MapProductor::Point<float> p = trans.transFromDispersedToContinuous(MapProductor::Point<int>{
					i, j, k
				});
				CreateStone(FVector(p.x,p.y,p.z));
			}
		}
	}
}





void UMapLauncher::CreateStone(FVector pos){
	//Ԥ����Ҫ����PositionTranslator��HEIGHT��EDGEWEIGHT���������ƽ������

}



