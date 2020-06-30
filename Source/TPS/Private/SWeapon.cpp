// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto owner = GetOwner();
	if (!IsValid(owner))
	{
		//不存在销毁事件
		if (!GetWorldTimerManager().IsTimerActive(DestroySelf))
		{
			FTimerDelegate func = FTimerDelegate::CreateLambda([=]() { Destroy(); });
			GetWorldTimerManager().SetTimer(DestroySelf, func, 3.0f, false);
		}


	}

}

