// Fill out your copyright notice in the Description page of Project Settings.


#include "Vitals.h"

// Sets default values for this component's properties
UVitals::UVitals()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UVitals::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Energy = MaxEnergy;
	Aux = MaxAux;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UVitals::TakeDamage);
	}
}

void UVitals::SetHealth(int value)
{
	if (value > MaxHealth) {
		Health = MaxHealth;
	}
	else {
		Health = value;
	};
}

void UVitals::SetEnergy(int value)
{
	if (value > MaxEnergy) {
		Energy = MaxEnergy;
	}
	else {
		Energy = value;
	};
}

void UVitals::SetAuxPower(int value)
{
	if (value > MaxAux) {
		Aux = MaxAux;
	}
	else {
		Aux = value;
	};
}

void UVitals::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bAllowDamage) {
		Health = FMath::Clamp(float(Health) - Damage, 0.0f, float(MaxHealth));
	};
}


// Called every frame
void UVitals::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MaxHealth == 0) {
		bAllowDamage = false;
	};

	if (Health <= 0 && MaxHealth > 0 && bAllowDamage == true) {
		GetOwner()->Destroy();
	};
}

