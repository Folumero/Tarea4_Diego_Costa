// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAttacktBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DamageCollisionEvaluator.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAbilityAttacktBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CanAttack)
	{
        AActor* Avatar = ActorInfo->AvatarActor.Get();

        check(Avatar);

        if (Avatar)
        {
            UCharacterMovementComponent* MoveComp = Avatar->FindComponentByClass<UCharacterMovementComponent>();
            if (MoveComp)
            {
                MoveComp->StopMovementImmediately();
                MoveComp->Deactivate();

            }

        }
        UDamageCollisionEvaluator* CollisionEvaluator = Avatar->FindComponentByClass<UDamageCollisionEvaluator>();
        if (CollisionEvaluator)
        {
            CollisionEvaluator->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ApplyDamageEffects);
        }

        UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
            UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay_);

        PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
        PlayMontageAndWait->Activate();
	}
	
}

void UAbilityAttacktBase::ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PONER EL DAÑO
    
}

void UAbilityAttacktBase::OnAnimationFinished()
{
    AActor* Avatar = CurrentActorInfo->AvatarActor.Get();
    UCharacterMovementComponent* MoveComp = Avatar->FindComponentByClass<UCharacterMovementComponent>();
    if (MoveComp)
    {
        MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);

        MoveComp->Activate();
    }

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);



}
