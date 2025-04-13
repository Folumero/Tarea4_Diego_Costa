// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAB_CameraLock.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced)
class UTHUB_GAS2025_API UGAB_CameraLock : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UGAB_CameraLock();

protected:
    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    UFUNCTION()
    void MantenerMirada();

    FTimerHandle LookTimerHandle;
    FRotator ObjetivoRotacion;

    const FGameplayAbilityActorInfo* SavedActorInfo = nullptr;
	
};
