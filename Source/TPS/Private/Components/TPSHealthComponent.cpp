// Fill out your copyright notice in the Description page of Project Settings.


#include "Components\TPSHealthComponent.h"

// Sets default values for this component's properties
UTPSHealthComponent::UTPSHealthComponent()
{
	MaxHealth = 100.0f;

}


// Called when the game starts
void UTPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor * MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UTPSHealthComponent::HandleTakeAnyDamage);
	}
	Health = MaxHealth;

}

void UTPSHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

