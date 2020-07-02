// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoneBase.generated.h"
class UStaticMeshComponent;

UCLASS()
class TPS_API AStoneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneBase();
	FIntVector position = FIntVector::ZeroValue;;
	

	UPROPERTY(VisibleAnywhere,Category="Components")
	UStaticMeshComponent *mesh;

	UPROPERTY(EditDefaultsOnly, Category = "CreationName")
		FString ClassName;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);



public:	
	UFUNCTION()
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
