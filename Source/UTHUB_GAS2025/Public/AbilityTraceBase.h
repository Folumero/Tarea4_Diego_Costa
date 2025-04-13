// AbilityTraceBase.h

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityTraceBase.generated.h"

UCLASS()
class UTHUB_GAS2025_API UAbilityTraceBase : public UGameplayAbility
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    UFUNCTION()
    void MantenerMiradaDeCamara();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
    bool bHabilitarMirada = false;



private:
    const FGameplayAbilityActorInfo* SavedActorInfo = nullptr;

    FRotator RotacionFijadaDeCamara;
    FRotator RotacionOriginalDeCamara;
    FVector PosicionOriginalDeCamara;
    FVector PawnDetectadoLocation;

    FTimerHandle CameraLookTimerHandle;



    bool bVolverASuavemente = false;
    bool test=true
	;

public:
    UFUNCTION(BlueprintCallable, Category = "Camara")
    void ResRotacionCameraBoom();

    FTimerHandle ResetCamaraTimerHandle;
    bool bReseteandoCamara = false;
    FRotator RotacionDestinoSuave;
    bool bPuedeSeleccionarObjetivo = true;
};

