// Fill out your copyright notice in the Description page of Project Settings.


#include "Vitals.h"

// Sets default values for this component's properties
UVitals::UVitals()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	MaxEnergy = 100;
	Health = MaxHealth;
	Energy = MaxEnergy;
}


// Called when the game starts
void UVitals::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UVitals::TakeDamage);
	}
}

// Called every frame
void UVitals::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(MaxHealth == 0)
	{
		bAllowDamage = false;
	}
	
	if(Health <= 0)
	{
		GetOwner()->Destroy();
	}
}

void UVitals::SetHealth(int value)
{
	if(value > MaxHealth)
	{
		Health = MaxHealth;
	} else if(value < 0) {
		Health = 0;
	} else {
		Health = value;
	}
}

void UVitals::SetEnergy(int value)
{
	if(value > MaxEnergy)
	{
		Energy = MaxEnergy;
	} else if(value < 0) {
		Energy = 0;
	} else {
		Energy = value;
	}
}

void UVitals::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bAllowDamage) {
		Health = FMath::Clamp(float(Health) - Damage, 0.0f, float(MaxHealth));
	};
}