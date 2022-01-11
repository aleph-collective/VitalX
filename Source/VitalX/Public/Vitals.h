// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Vitals.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VITALX_API UVitals : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVitals();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		bool bAllowDamage = true;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character: Health")
		int MaxHealth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character: Health")
		int Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character: Energy")
		int MaxEnergy;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character: Energy")
		int Energy;

	UFUNCTION(BlueprintPure, Category = "Character: Health")
		int GetHealth() const { return Health; }
	UFUNCTION(Exec, BlueprintCallable, Category = "Character: Health")
		void SetHealth(int value);

	UFUNCTION(BlueprintPure, Category = "Character: Energy")
		int GetEnergy() const { return Energy; }
	UFUNCTION(Exec, BlueprintCallable, Category = "Character: Energy")
		void SetEnergy(int value);

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
