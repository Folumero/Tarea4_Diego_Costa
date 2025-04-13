#include "AbilityTraceBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

void UAbilityTraceBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    SavedActorInfo = ActorInfo;
    AActor* Avatar = ActorInfo->AvatarActor.Get();


    APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController.Get());

    FVector WorldLocation, WorldDirection;
    if (!PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) return;

    FVector TraceStart = WorldLocation;
    FVector TraceEnd = TraceStart + WorldDirection * 10000.0f;

    TArray<FHitResult> HitResults;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Avatar);

    float SphereRadius = 100.0f;
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(SphereRadius);

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        TraceStart,
        TraceEnd,
        FQuat::Identity,
        ECC_Pawn,
        SphereShape,
        Params
    );

    bHabilitarMirada = false;
    bVolverASuavemente = false;


    for (const FHitResult& Hit : HitResults)
    {
        APawn* Pawn = Cast<APawn>(Hit.GetActor());
        if (Pawn)
        {
            bHabilitarMirada = true;
            PawnDetectadoLocation = Pawn->GetActorLocation();

            ACharacter* MyChar = Cast<ACharacter>(Avatar);
            if (MyChar)
            {
                USpringArmComponent* CameraBoom = MyChar->FindComponentByClass<USpringArmComponent>();
                if (CameraBoom)
                {
                    RotacionOriginalDeCamara = CameraBoom->GetComponentRotation();

                    GetWorld()->GetTimerManager().ClearTimer(CameraLookTimerHandle);
                    GetWorld()->GetTimerManager().SetTimer(
                        CameraLookTimerHandle,
                        this,
                        &UAbilityTraceBase::MantenerMiradaDeCamara,
                        0.01f,
                        true
                    );
                }
            }

            break; 
        }
    }

    // si no se detectó ningún Pawn
    if (!bHabilitarMirada)
    {

        GetWorld()->GetTimerManager().ClearTimer(CameraLookTimerHandle);
        GetWorld()->GetTimerManager().SetTimer(
            CameraLookTimerHandle,
            this,
            &UAbilityTraceBase::MantenerMiradaDeCamara,
            0.01f,
            true
        );

    }
}

void UAbilityTraceBase::MantenerMiradaDeCamara()
{
    if (!SavedActorInfo || !SavedActorInfo->AvatarActor.IsValid()) return;

    ACharacter* MyChar = Cast<ACharacter>(SavedActorInfo->AvatarActor.Get());
    if (!MyChar) return;

    USpringArmComponent* CameraBoom = MyChar->FindComponentByClass<USpringArmComponent>();
    if (!CameraBoom) return;

    FRotator CurrentRot = CameraBoom->GetComponentRotation();
    FRotator TargetRot;

    if (bHabilitarMirada)
    {
        FVector From = CameraBoom->GetComponentLocation();
        FVector To = PawnDetectadoLocation;
        To.Z = From.Z;

        TargetRot = UKismetMathLibrary::FindLookAtRotation(From, To);
        TargetRot.Pitch = CurrentRot.Pitch;
        TargetRot.Roll = CurrentRot.Roll;
    }
    else if (bVolverASuavemente)
    {
        TargetRot = FRotator(-50.0f, 0.0f, 0.0f);
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(CameraLookTimerHandle);
        return;
    }

    FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, GetWorld()->GetDeltaSeconds(), 5.0f);
    CameraBoom->SetWorldRotation(NewRot);

    if (!bHabilitarMirada && bVolverASuavemente && NewRot.Equals(TargetRot, 0.5f))
    {
        CameraBoom->SetWorldRotation(TargetRot);

        GetWorld()->GetTimerManager().ClearTimer(CameraLookTimerHandle);
        bVolverASuavemente = false;

    }
}

void UAbilityTraceBase::ResRotacionCameraBoom()
{
    if (!SavedActorInfo || !SavedActorInfo->AvatarActor.IsValid()) return;

    ACharacter* MyChar = Cast<ACharacter>(SavedActorInfo->AvatarActor.Get());
    if (!MyChar) return;

    USpringArmComponent* CameraBoom = MyChar->FindComponentByClass<USpringArmComponent>();
    if (!CameraBoom) return;

    bHabilitarMirada = false;
    bVolverASuavemente = true;

    // Forzamos el timer si aún no está activo
    if (!GetWorld()->GetTimerManager().IsTimerActive(CameraLookTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(
            CameraLookTimerHandle,
            this,
            &UAbilityTraceBase::MantenerMiradaDeCamara,
            0.01f,
            true
        );
    }
}