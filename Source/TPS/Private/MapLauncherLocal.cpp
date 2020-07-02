// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLauncherLocal.h"
#include "MapLauncher.h"
#include "StoneBase.h"

// Sets default values for this component's properties
UMapLauncherLocal::UMapLauncherLocal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMapLauncherLocal::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMapLauncherLocal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AStoneBase *UMapLauncherLocal::CreateStone(const FString& BP_Name, const FIntVector& pos) {
	if (BP_Name == "") {
		AStoneBase *x = StoneMap.FindRef(pos);
		if(x){
			x->Destroy();
			StoneMap.Remove(pos);
		}
		return nullptr;
	}
	if (StoneMap.FindRef(pos)) {
		return nullptr;
	}
	FString s = "Blueprint'/Game/Blueprints/";
	s += BP_Name + ".";
	s += BP_Name + "_C'";
	//	UE_LOG(LogTemp, Log, TEXT(&s[0]));

	UClass* BlueprintVar = StaticLoadClass(AStoneBase::StaticClass(), nullptr, &s[0]);
	if (BlueprintVar != nullptr)
	{
		// 向场景中添加新生成的蓝图实例

		AStoneBase* pMyActor =GetWorld()->SpawnActor<AStoneBase>(BlueprintVar,UMapLauncher::getInstance()-> transFromDispersedToContinuous(pos), FRotator::ZeroRotator);
		if (pMyActor)
		{
			pMyActor->position = pos;
		//	UE_LOG(LogTemp, Log, TEXT("!!!new obj z :%f"), transFromDispersedToContinuous(pos).Z);
			StoneMap.Add(TTuple<FIntVector, AStoneBase*>(pos, pMyActor));
			return pMyActor;
		}
	}
	return nullptr;
}