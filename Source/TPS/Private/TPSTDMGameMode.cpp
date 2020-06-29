// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTDMGameMode.h"
#include "TPSPlayerState.h"
#include "TPSGameState.h"




ATPSTDMGameMode::ATPSTDMGameMode()
{
	PlayerStateClass = ATPSPlayerState::StaticClass();
	GameStateClass = ATPSGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.15f;

}

void ATPSTDMGameMode::StartPlay()
{
	Super::StartPlay();


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
	UE_LOG(LogTemp, Log, TEXT("Truly Respawning !"));
	if (Controller)
	{
		UE_LOG(LogTemp, Log, TEXT("Real Controller !"));
	}
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
				// @TODO;
			}
		}
	}
		

}

void ATPSTDMGameMode::Tick(float DeltaSeconds)
{
	AssignNewTeamId();
}

void ATPSTDMGameMode::GameOver()
{
	// @TODO Finish up the match
}


