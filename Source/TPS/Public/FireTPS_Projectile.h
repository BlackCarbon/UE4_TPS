// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPS_Projectile.h"
#include "FireTPS_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AFireTPS_Projectile : public ATPS_Projectile
{
public:
	AFireTPS_Projectile();


private:



public:
	GENERATED_BODY()
		//virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
