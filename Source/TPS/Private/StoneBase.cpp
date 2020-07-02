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
	//this->SetRootComponent(mesh);
//	mesh->SetAttachParent(GetRootComponent());
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
		FVector loc = Hit.Location - GetTransform().GetLocation();
		
		/*
		float var = loc.Z / mesh->GetComponentTransform().GetScale3D().Z;
		if (abs(round(var) - var) < 1e-6) {
			Destroy();
		}*/
		if (loc.Z > 40) {//打在砖块顶面
			FIntVector np = position;
			np.Z += 1;
			if (other->GetActorLabel().StartsWith("BP_Fire")) {

				UMapLauncher::getInstance()->TryCreateStone("BP_Fire", np);
			}
			else if (other->GetActorLabel().StartsWith("BP_Witer")) {

				UMapLauncher::getInstance()->TryCreateStone("BP_Water", np);
			}
		}
		else {//打在砖块侧面
			UMapLauncher::getInstance()->TryCreateStone("", position);
		}
		UE_LOG(LogTemp, Log, TEXT("z :%f"), loc.Z);
	}
}

