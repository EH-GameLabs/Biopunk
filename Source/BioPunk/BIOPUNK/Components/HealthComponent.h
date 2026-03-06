// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BIOPUNK/Interfaces/Damageable.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


// Delegate signature
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageSignature, int32, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, int32, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIOPUNK_API UHealthComponent : public UActorComponent, public IDamageable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void NativeTakeDamage(AActor* Interactor, float Damage) override;
	
	UFUNCTION()
	virtual void NativeDie() override;
	
	UFUNCTION()
	inline float GetHealth() const { return Health; } 
	
	void SetHealth(float const NewHealth);
	
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageSignature OnTakeDamage;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnDieSignature OnDie;
};
