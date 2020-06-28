// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSTDMGameMode.h"
#include "TPSPlayerState.h"




ATPSTDMGameMode::ATPSTDMGameMode()
{

	PlayerStateClass = ATPSPlayerState::StaticClass();


}


void ATPSTDMGameMode::RespawnPlayer(AController * Controller)
{
	UE_LOG(LogTemp, Log, TEXT("What the hell ?"));
	//同一个世界，同一个梦想。
	if (Controller)
	{
		UE_LOG(LogTemp, Log, TEXT("Test1 passed"));
	}
	if (Controller && Controller->GetWorld() == GetWorld())
	{
		UE_LOG(LogTemp, Log, TEXT("Test2 passed"));
	}
	if (Controller && Controller->GetPawn() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Test3 passed"));
	}
	if (Controller && Controller->GetWorld() == GetWorld() && Controller->GetPawn() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("What the hell !!!"));
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

void ATPSTDMGameMode::GameOver()
{
	// @TODO Finish up the match
}


