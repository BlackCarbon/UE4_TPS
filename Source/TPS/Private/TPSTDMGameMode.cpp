// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTDMGameMode.h"
#include "TPSPlayerState.h"




ATPSTDMGameMode::ATPSTDMGameMode()
{

	PlayerStateClass = ATPSPlayerState::StaticClass();


}


void ATPSTDMGameMode::RespawnPlayer(APlayerController * Controller)
{
	//同一个世界，同一个梦想。
	if (Controller && Controller->GetWorld() == GetWorld() && Controller->GetPawn() == nullptr)
	{
		RestartPlayer(Controller);
	}
}

void ATPSTDMGameMode::RespawnPlayer(APlayerController * Controller, float InTime)
{
	FTimerHandle uselessHandler;
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &ATPSTDMGameMode::RespawnPlayer, Controller);
	GetWorldTimerManager().SetTimer(uselessHandler, RespawnDelegate, InTime, false);
}

void ATPSTDMGameMode::GameOver()
{
	// @TODO Finish up the match
}


