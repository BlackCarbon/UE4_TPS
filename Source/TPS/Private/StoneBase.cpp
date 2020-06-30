// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneBase.h"
#include "TPS_Projectile.h"
#include "MapLauncher.h"

// Sets default values
AStoneBase::AStoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Static Mesh"));
//	mesh->SetCollisionProfileName(TEXT("BlackAll"));
	//mesh->GetComponentToWorld().SetScale3D(FVector(50));
//	mesh=
}

// Called when the game starts or when spawned
void AStoneBase::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentHit.AddDynamic(this, &AStoneBase::OnHit);

}

// Called every frame
void AStoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AStoneBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	ATPS_Projectile *other = Cast<ATPS_Projectile>(OtherActor);
	if(other)
	{
		float var = Hit.Location.Z / mesh->GetComponentTransform().GetScale3D().Z;
		if (abs(round(var) - var) < 1e-6) {
			Destroy();
		}
		UE_LOG(LogTemp, Log, TEXT("Z %f"), Hit.Location.Z);
	}
}

AStoneBase* AStoneBase::CreateStone(FIntVector pos) {
	//AStoneBase* x =GetWorld()-> SpawnActor<AStoneBase>(AStoneBase::StaticClass(),UMapLauncher->getInstance()->transFromDispersedToContinuous(pos));
	//return x;
	return nullptr;
}
