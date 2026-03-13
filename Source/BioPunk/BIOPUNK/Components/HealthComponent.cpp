// Fill out your copyright notice in the Description page of Project Settings.


#include "BIOPUNK/Components/HealthComponent.h"

#include "BIOPUNK/Core/CleanCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnDie.AddDynamic(this, &UHealthComponent::NativeDie);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::NativeTakeDamage(AActor* Interactor, float Damage)
{
	IDamageable::NativeTakeDamage(Interactor, Damage);
	
	AActor* owner = GetOwner();
	if (ACleanCharacter* Character = Cast<ACleanCharacter>(owner))
	{
		if (Character->bIsDashing) return;
	}
	
	float RealDamage = Damage * DamageMultiplier;
	SetHealth(Health - RealDamage);
	
	// lancio evento di TakeDamage
	OnTakeDamage.Broadcast(Damage);
}

void UHealthComponent::NativeDie()
{
	IDamageable::NativeDie();
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.5f,
		FColor::Black,
		FString::Printf(TEXT("MORTO"))
	);
}

void UHealthComponent::SetHealth(float const NewHealth)
{
	if (Health == NewHealth) return;
	
	Health = NewHealth;
	
	// lancio evento di cambio vita
	OnHealthChange.Broadcast(NewHealth);
	
	// controllo se è morto
	if (Health <= 0.0f)
	{
		OnDie.Broadcast();
	}
}

