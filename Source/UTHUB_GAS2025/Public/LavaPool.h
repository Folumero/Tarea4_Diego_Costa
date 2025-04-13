//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "GameplayEffect.h"
//#include "Components/BoxComponent.h"
//#include "LavaPool.generated.h"
//
//UCLASS()
//class UTHUB_GAS2025_API ALavaPool : public AActor
//{
//    GENERATED_BODY()
//
//public:
//    ALavaPool();
//
//protected:
//    virtual void BeginPlay() override;
//
//    UPROPERTY(VisibleAnywhere, Category = "Lava")
//    UBoxComponent* CollisionBox;
//
//    UPROPERTY(EditDefaultsOnly, Category = "Lava")
//    TSubclassOf<UGameplayEffect> LavaDamageEffect;
//
//    UFUNCTION()
//    static void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
//        bool bFromSweep, const FHitResult& SweepResult);
//
//    UFUNCTION()
//    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
//
//    TMap<AActor*, FActiveGameplayEffectHandle> ActiveEffects;
//};
