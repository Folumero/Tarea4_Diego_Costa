#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VirusComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UVirusComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UVirusComponent();

protected:
    virtual void BeginPlay() override;


public:
    void CheckForInfection();
    void Infect(AActor* Target);

private:
    UPROPERTY(EditAnywhere, Category = "Virus")
    float InfectionRadius = 300.0f;

    UPROPERTY(EditAnywhere, Category = "Virus")
    float CheckFrequency = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Virus")
    TSubclassOf<UGameplayEffect> VirusEffect;

    FTimerHandle InfectionCheckTimer;
};
