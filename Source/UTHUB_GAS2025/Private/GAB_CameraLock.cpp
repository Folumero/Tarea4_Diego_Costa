#include "GAB_CameraLock.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"

UGAB_CameraLock::UGAB_CameraLock()
{
    //InstancingPolicy = EGameplayAbilityInstancingPolicy::Instanced;
}

void UGAB_CameraLock::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    SavedActorInfo = ActorInfo;

    APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController.Get());
    if (!PC) return;

    FVector WorldLocation, WorldDirection;
    if (!PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) return;

    FVector TraceStart = WorldLocation;
    FVector TraceEnd = TraceStart + WorldDirection * 10000.0f;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(ActorInfo->AvatarActor.Get());

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Pawn, Params);

    if (bHit && HitResult.GetActor())
    {
        FVector PawnLocation = HitResult.GetActor()->GetActorLocation();

        ACharacter* MyChar = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
        if (!MyChar) return;

        USpringArmComponent* CameraBoom = MyChar->FindComponentByClass<USpringArmComponent>();
        if (!CameraBoom) return;

        FVector From = CameraBoom->GetComponentLocation();
        PawnLocation.Z = From.Z;

        FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(From, PawnLocation);
        LookAtRot.Pitch = CameraBoom->GetComponentRotation().Pitch;

        ObjetivoRotacion = LookAtRot;

        FTimerDelegate TimerDel;
        TimerDel.BindUFunction(this, FName("MantenerMirada"));

        GetWorld()->GetTimerManager().SetTimer(
            LookTimerHandle,
            TimerDel,
            0.01f,
            true
        );

        UE_LOG(LogTemp, Warning, TEXT("Objetivo fijado. Comenzando rotación continua."));
    }
}

void UGAB_CameraLock::MantenerMirada()
{
    if (!SavedActorInfo || !SavedActorInfo->AvatarActor.IsValid()) return;

    ACharacter* MyChar = Cast<ACharacter>(SavedActorInfo->AvatarActor.Get());
    if (!MyChar) return;

    USpringArmComponent* CameraBoom = MyChar->FindComponentByClass<USpringArmComponent>();
    if (!CameraBoom) return;

    CameraBoom->SetWorldRotation(ObjetivoRotacion);
}
