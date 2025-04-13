// ScanSphereActor.cpp

#include "ScanSphereActor.h"

#include "ABP_NPC.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

AScanSphereActor::AScanSphereActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;

    SphereComponent->InitSphereRadius(100.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SphereComponent->SetGenerateOverlapEvents(true);

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AScanSphereActor::OnSphereBeginOverlap);
}

void AScanSphereActor::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(2.0f);
}

void AScanSphereActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        AActor* DetectedCharacter = Cast<AABP_NPC>(OtherActor);
        if (DetectedCharacter)
        {
            FVector WorldLocation = DetectedCharacter->GetActorLocation();
           

            DetectedTargetTransform = DetectedCharacter->GetActorTransform();

            OnTargetDetected.Broadcast(DetectedTargetTransform);

            UE_LOG(LogTemp, Warning, TEXT("Transform detectado:\n%s"), *DetectedTargetTransform.ToString());

            Destroy();
        }
    }
}
