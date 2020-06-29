// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameState.h"
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

	
	void SetGameStatus(EGameStatus NewStatus);

	EGameStatus QueryGameStatus();

	void AssignNewTeamId();

	void PreparingForGame();

	void StartGame();

	void EndGame();

	void GameOver();

	void Tick(float DeltaSeconds) override;



public:

	ATPSTDMGameMode();

	void StartPlay() override;


	void RespawnPlayer(AController * Controller, float InTime);

	void RespawnPlayer(AController * Controller);

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
		FOnActorKilled OnActorKilled;



};
