// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Controller.h"
#include "Chaos/Pair.h"
#include "TPSGameState.generated.h"


UENUM(BlueprintType)
enum class EGameStatus : uint8
{
	Idle,
	PreparingGame,
	InGame,
	GameFinished
};


/**
 *
 */
UCLASS()
class TPS_API ATPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ATPSGameState();

	//����б�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
		TMap<AController*,int> playerList;

	//�����Ŷ�����Ϣ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
		TMap<int,int> TeamStates;


	//���ظ���ҵĶ��飬δע����򷵻�0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamState(int playerIndex);

	//���ظ���ҵĶ��飬δע����򷵻�0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamStateByActor(AActor *player);

	//���ظ���ҵĶ��飬δע����򷵻�0
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int GetTeamStateByController(AController *player);

	//���ظö���ĳ�Ա��
	UFUNCTION(BlueprintCallable, Category = "GameState")
		int TeamCount(int team);


	void AddNewPlayer(AController* player,int playerId);

	//�Ծ�״̬
	UPROPERTY(ReplicatedUsing=OnRep_GameStatus , BlueprintReadOnly, Category = "GameState")
		EGameStatus GameStatus;

protected:

	UFUNCTION()
		void OnRep_GameStatus(EGameStatus OldStatus);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
		void OnGameStatusChanged(EGameStatus NewStatus, EGameStatus OldStatus);

};
