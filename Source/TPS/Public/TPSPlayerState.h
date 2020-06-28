// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
		void IncreaseScore(float DeltaScore);

	
};
