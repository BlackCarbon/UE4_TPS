// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSTDMGameMode.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);



/**
 * 
 */
UCLASS()
class TPS_API ATPSTDMGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	void GameOver();


public:

	ATPSTDMGameMode();
	

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
		FOnActorKilled OnActorKilled;

};
