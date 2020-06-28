// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameState.h"
#include "Net\Unrealnetwork.h"
#include <ctime>
#include <utility>

ATPSGameState::ATPSGameState()
{
	if (HasAuthority())
	{
		playerList.Empty();
		srand(time(nullptr));
	}

	TeamStates.Empty();
}





int ATPSGameState::GetTeamState(int playerIndex)
{
	if (TeamStates.Contains(playerIndex))
		return TeamStates[playerIndex];
	else
		return 0;
}

int ATPSGameState::GetTeamStateByController(AController* Controller)
{
	return GetTeamState(GetPlayerIndex(Controller));
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
	playerList.Add(player);
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

void ATPSGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(ATPSGameState, TeamStates);
}