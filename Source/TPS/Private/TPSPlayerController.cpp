// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "Net\UnrealNetwork.h"



void ATPSPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSPlayerController, TeamID);

}