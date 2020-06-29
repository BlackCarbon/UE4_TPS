// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Controller.h"
#include "Chaos/Pair.h"
#include "TPSGameState.generated.h"




/**
 *
 */
UCLASS()
class TPS_API ATPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ATPSGameState();

	//玩家列表
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
		TMap<AController*,int> playerList;

	//储存着队伍信息
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
		TMap<int,int> TeamStates;


	//返回该玩家的队伍，未注册的则返回0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamState(int playerIndex);

	//返回该玩家的队伍，未注册的则返回0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamStateByActor(AActor *player);

	//返回该玩家的队伍，未注册的则返回0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamStateByController(AController *player);

	//返回该队伍的成员数
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int TeamCount(int team);


	void AddNewPlayer(AController* player,int playerId);

};
