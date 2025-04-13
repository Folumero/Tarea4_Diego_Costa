#include "AbilityDash.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void UAbilityDash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    AActor* Avatar = ActorInfo->AvatarActor.Get();

    ACharacter* Character = Cast<ACharacter>(Avatar);

    UCharacterMovementComponent* MoveComp = Character->FindComponentByClass<UCharacterMovementComponent>();

    FVector DashDirection = Character->GetActorForwardVector().GetSafeNormal();
    float DashStrength = 1200.0f;

    // Lanza el personaje
    MoveComp->BrakingFrictionFactor = 0.f;
    MoveComp->Launch(DashDirection * DashStrength);

    FTimerDelegate ResetFrictionDelegate;
    ResetFrictionDelegate.BindLambda([MoveComp]()
        {
            MoveComp->BrakingFrictionFactor = 2.0f; // Valor normal
        });

    FTimerHandle TimerHandle;
    Avatar->GetWorldTimerManager().SetTimer(TimerHandle, ResetFrictionDelegate, 0.2f, false);

}
