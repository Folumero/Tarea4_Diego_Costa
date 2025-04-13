// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityIsDashing.h"
#include "AbilityDash.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UAbilityDash : public UAbilityIsDashing
{
	GENERATED_BODY()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


	
};
