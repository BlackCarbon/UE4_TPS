// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTDMGameMode.h"
#include "TPSPlayerState.h"
#include "TPSGameState.h"
#include "TPSCharacter.h"
#include "GameFramework/PawnMovementComponent.h"





ATPSTDMGameMode::ATPSTDMGameMode()
{
	PlayerStateClass = ATPSPlayerState::StaticClass();
	GameStateClass = ATPSGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.15f;

}


void ATPSTDMGameMode::SetGameStatus(EGameStatus NewStatus)
{
	ATPSGameState *GS = GetGameState<ATPSGameState>();
	if (ensureAlways(GS))
	{
		GS->GameStatus = NewStatus;
	}
}




EGameStatus ATPSTDMGameMode::QueryGameStatus()
{
	ATPSGameState *GS = GetGameState<ATPSGameState>();
	if (ensureAlways(GS))
	{
		return GS->GameStatus;
	}
	UE_LOG(LogTemp, Warning, TEXT("GameState doesn't exist!"));
	return EGameStatus::Idle;
}

void ATPSTDMGameMode::StartPlay()
{
	Super::StartPlay();
	//׼����Ϸ
	PreparingForGame();

}


void ATPSTDMGameMode::RespawnPlayer(AController * Controller)
{
// 	UE_LOG(LogTemp, Log, TEXT("What the hell ?"));
	//ͬһ�����磬ͬһ�����롣
	if (Controller && Controller->GetWorld() == GetWorld() && Controller->GetPawn() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Respawn successfully!"));
		RestartPlayer(Controller);
	}
}

void ATPSTDMGameMode::RespawnPlayer(AController * Controller, float InTime)
{
// 	UE_LOG(LogTemp, Log, TEXT("Truly Respawning !"));
// 	if (Controller)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("Real Controller !"));
// 	}
	FTimerHandle uselessHandler;
	FTimerDelegate func = FTimerDelegate::CreateLambda([=]() { RespawnPlayer(Controller); });
	GetWorldTimerManager().SetTimer(uselessHandler, func, InTime, false);
}





void ATPSTDMGameMode::AssignNewTeamId()
{
	auto World = GetWorld();
	auto GS = GetGameState<ATPSGameState>();
	if (World && GS)
	{
		for (auto It = World->GetPlayerControllerIterator(); It; ++It)
		{
			auto PC = It->Get();
			if (!GS->playerList.Contains(PC))
			{
				auto PS = PC->GetPlayerState<ATPSPlayerState>();
				if (PS)
				{
					GS->AddNewPlayer(PC, PS->GetPlayerId());
				}
			}
		}
	}
		

}

void ATPSTDMGameMode::PreparingForGame()
{
	//��Ϸֻ׼��һ��
	if (QueryGameStatus() == EGameStatus::PreparingGame)
	{
		return;
	}
	SetGameStatus(EGameStatus::PreparingGame);

	//������һ�����ܹ����Handler������45s��ʼ��Ϸ
	
	FTimerHandle uselessHandle;
	GetWorldTimerManager().SetTimer(uselessHandle, this, &ATPSTDMGameMode::StartGame, 45.0f, false);

}




void ATPSTDMGameMode::StartGame()
{
	//��Ϸֻ��ʼһ��
	if (QueryGameStatus() == EGameStatus::InGame)
	{
		return;
	}
	SetGameStatus(EGameStatus::InGame);
}

void ATPSTDMGameMode::EndGame()
{
	//��Ϸֻ����һ��
	if (QueryGameStatus() == EGameStatus::GameFinished)
	{
		return;
	}
	SetGameStatus(EGameStatus::GameFinished);
	GameOver();
}

void ATPSTDMGameMode::GameOver()
{
	auto world = GetWorld();
	if (ensureAlways(world))
	{
		for (auto It = world->GetPlayerControllerIterator(); It; ++It)
		{
			auto PC = It->Get();
			if(ensure(PC))
			{
				auto character = Cast<ATPSCharacter>(PC->GetCharacter());
				if (ensure(character))
				{
					//ֹͣ�ƶ������������
					character->GetMovementComponent()->StopMovementImmediately();
					character->DetachFromControllerPendingDestroy();
				}
			}
		}
	}

	// @TODO ������ҽ����ɲٿ�
}

void ATPSTDMGameMode::ClearScore()
{
	auto world = GetWorld();
	if (ensureAlways(world))
	{
		for (auto It = world->GetPlayerControllerIterator(); It; ++It)
		{
			auto PC = It->Get();
			if (PC)
			{
				auto PS = PC->GetPlayerState<ATPSPlayerState>();
				PS->SetScore(0);
			}
		}
	}
}

float ATPSTDMGameMode::QueryTeamScore(int team)
{
	auto world = GetWorld();
	if (ensureAlways(world))
	{
		auto GS = world->GetGameState<ATPSGameState>();
		if (ensure(GS))
		{
			if (team == 0)
			{
				return GS->TeamAScore;
			}
			else
			{
				return GS->TeamBScore;
			}
		}
	}
	return 0;
}

void ATPSTDMGameMode::SetTeamScore(int team, float count)
{
	auto world = GetWorld();
	if (ensureAlways(world))
	{
		auto GS = world->GetGameState<ATPSGameState>();
		if (ensure(GS))
		{
			if (team == 0)
			{
				GS->TeamAScore = count;
			}
			else
			{
				GS->TeamBScore = count;
			}
			float eps = 1e-4;
			//�ж����ʤ
			if (GS->TeamAScore >= 100.0f - eps || GS->TeamBScore >= 100.0f - eps)
			{
				EndGame();
			}
		}
	}
}

void ATPSTDMGameMode::AddTeamScore(int team, float count)
{
	SetTeamScore(team, QueryTeamScore(team) + count);
}

void ATPSTDMGameMode::Tick(float DeltaSeconds)
{
	AssignNewTeamId();
}




