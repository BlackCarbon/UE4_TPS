// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MapLauncherLocal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_API UMapLauncherLocal : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMapLauncherLocal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TMap<FIntVector, AStoneBase*>StoneMap;
	UFUNCTION()
	AStoneBase *CreateStone(const FString &BP_Name,const FIntVector &pos);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
