// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameState.h"
#include "Net\Unrealnetwork.h"
#include <ctime>
#include <utility>
#include <TPSCharacter.h>

ATPSGameState::ATPSGameState()
{
	if (HasAuthority())
	{
		playerList.Empty();
		srand(time(nullptr));
	}
	GameStatus = EGameStatus::Idle;
	TeamAScore = TeamBScore = 0;
	TeamStates.Empty();
}





int ATPSGameState::GetTeamState(int playerIndex)
{
	if (TeamStates.Contains(playerIndex))
		return TeamStates[playerIndex];
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Doesn't exist playerIndex : %d"), playerIndex);
		return 0;
	}
}


int ATPSGameState::GetTeamStateByController(AController *player)
{
	if (playerList.Contains(player))
		return GetTeamState(playerList[player]);
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Doesn't exist such player"));
		return 0;
	}

}

int ATPSGameState::GetTeamStateByActor(AActor * player)
{
	auto character = Cast<ATPSCharacter>(player);
	if (ensureAlways(character))
	{
		return GetTeamStateByController(character->GetController());
	}
	UE_LOG(LogTemp, Warning, TEXT("Doesn't exist such player"));
	return 0;
}




int ATPSGameState::TeamCount(int team)
{
	int cnt = 0;
	for (auto it : TeamStates)
	{
		if (it.Value == team)
		{
			cnt++;
		}
	}
	return cnt;
}


void ATPSGameState::AddNewPlayer(AController* player,int playerId)
{
	playerList.Add(player, playerId);
	int zerocnt = TeamCount(0);
	int onecnt = TeamCount(1);
	if (onecnt == zerocnt)
	{
		TeamStates.Add(playerId, rand() & 1);
	}
	else
	{
		TeamStates.Add(playerId, onecnt < zerocnt);
	}
}

void ATPSGameState::OnRep_GameStatus(EGameStatus OldStatus)
{
	OnGameStatusChanged(GameStatus, OldStatus);
}

void ATPSGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSGameState, GameStatus);
	DOREPLIFETIME(ATPSGameState, TeamAScore);
	DOREPLIFETIME(ATPSGameState, TeamBScore);
}