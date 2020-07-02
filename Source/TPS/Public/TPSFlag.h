// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSFlag.generated.h"



class UStaticMeshComponent;
class UBoxComponent;

UCLASS(BlueprintType)
class TPS_API ATPSFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSFlag();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FLAG")
		UStaticMeshComponent* flag;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FLAG")
	int flagteam;

public:	

	UFUNCTION()
	int getFlagTeam()
	{
		return flagteam;
	}

	UFUNCTION(BlueprintImplementableEvent, Category = "MyFunc")
	void SetSpeed(int speed);

	UFUNCTION(BlueprintImplementableEvent, Category = "MyFunc")
	void FireFlag();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyFunc")
	void WaterFlag();

};
