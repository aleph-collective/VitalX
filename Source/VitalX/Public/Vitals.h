#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Vitals.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VITALX_API UVitals : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UVitals();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Settings")
		int MaxHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Settings")
		int MaxEnergy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Settings")
		int MaxAuxPower;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Settings")
		bool bAllowDamage = true;
	
	UFUNCTION(BlueprintPure, Category="Character|Health")
		int GetHealth() const;
	UFUNCTION(BlueprintCallable, Category="Character|Health")
		static void SetHealth(int Value);
	
	UFUNCTION(BlueprintPure, Category="Character|Energy")
		int GetEnergy() const;
	UFUNCTION(BlueprintCallable, Category="Character|Energy")
		static void SetEnergy(int Value);
	UFUNCTION(BlueprintCallable, Category="Character|Energy")
		static void RemoveEnergy(int Value);
	UFUNCTION(BlueprintCallable, Category="Character|Energy")
		void EnergyFail(int Value);
	
	UFUNCTION(BlueprintPure, Category="Character|Aux")
		int GetAuxPower() const;
	UFUNCTION(BlueprintCallable, Category="Character|Aux")
		static void SetAuxPower(int Value);
	UFUNCTION(BlueprintCallable, Category="Character|Aux")
		static void RemoveAuxPower(int Value);
	UFUNCTION(BlueprintCallable, Category="Character|Aux")
		void AuxPowerFail(int Value);
};