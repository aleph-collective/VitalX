#include "Vitals.h"
#include "CSL_Window.h"

int Health;
int HealthLimit;

int Energy;
int EnergyLimit;

int AuxPower;
int AuxPowerLimit;

UVitals::UVitals()
{
	MaxHealth = 100;
	MaxEnergy = 100;
	MaxAuxPower = 100;

	// NOTE: The limit values are used in the Set and Remove functions. I might change this at a later date.
	
	Health = MaxHealth;
	HealthLimit = MaxHealth;

	Energy = MaxEnergy;
	EnergyLimit = MaxEnergy;

	AuxPower = MaxAuxPower;
	AuxPowerLimit = MaxAuxPower;

	if(MaxHealth <= 0)
	{
		bAllowDamage = false;
	}
}

void UVitals::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(Health <= 0)
	{
		GetOwner()->Destroy();
	}
}

void UVitals::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UVitals::TakeDamage);
	}
}

void UVitals::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (bAllowDamage) {
		Health = FMath::Clamp(float(Health) - Damage, 0.0f, float(MaxHealth));
	}
}

int UVitals::GetHealth() const
{
	return Health;
}

void UVitals::SetHealth(int Value)
{
	if(Value > HealthLimit)
	{
		Health = HealthLimit;
	} else if(Value < 0) {
		Health = 0;
	} else {
		Health = Value;
	}
}

int UVitals::GetEnergy() const
{
	return Energy;
}

void UVitals::SetEnergy(int Value)
{
	if(Value > EnergyLimit)
	{
		Energy = EnergyLimit;
	} else if(Value < 0) {
		Energy = 0;
	} else {
		Energy = Value;
	}
}

void UVitals::RemoveEnergy(int Value)
{
	SetEnergy(Energy - Value);
}

void UVitals::EnergyFail(int Value)
{
	if(Energy < Value)
	{
		UCSL_Window::PrintToConsole(this->GetName(), "Warning", FString::Printf(TEXT("You need %i more Energy."), Value - Energy));
	}
}

int UVitals::GetAuxPower() const
{
	return AuxPower;
}

void UVitals::SetAuxPower(int Value)
{
	if(Value > AuxPowerLimit)
	{
		AuxPower = AuxPowerLimit;
	} else if(Value < 0) {
		AuxPower = 0;
	} else {
		AuxPower = Value;
	}
}

void UVitals::RemoveAuxPower(int Value)
{
	SetAuxPower(AuxPower - Value);
}

void UVitals::AuxPowerFail(int Value)
{
	if(AuxPower < Value)
	{
		UCSL_Window::PrintToConsole(this->GetName(), "Warning", FString::Printf(TEXT("You need %i more Aux Power."), Value - AuxPower));
	}
}
