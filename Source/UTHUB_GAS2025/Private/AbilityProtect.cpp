// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityProtect.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAbilityProtect::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    AActor* Avatar = ActorInfo->AvatarActor.Get();

    check(Avatar);

    if (Avatar)
    {
        UCharacterMovementComponent* MoveComp = Avatar->FindComponentByClass<UCharacterMovementComponent>();
        if (MoveComp)
        {
            MoveComp->StopMovementImmediately();
            MoveComp->Deactivate();

            if (ActorToSpawn)
            {
                FVector Forward = Avatar->GetActorForwardVector();
                FVector SpawnLocation = Avatar->GetActorLocation() + Forward * 100.f;
                FRotator SpawnRotation = Avatar->GetActorRotation();

                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = Avatar;
                SpawnParams.Instigator = Cast<APawn>(Avatar);

                GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
            }

        }

    }

    UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
        UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay_);

    PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
    PlayMontageAndWait->Activate();
}

void UAbilityProtect::OnAnimationFinished()
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
