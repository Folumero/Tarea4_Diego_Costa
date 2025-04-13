// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScanSphereActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDetected, const FTransform&, TargetTransform);
UCLASS()
class UTHUB_GAS2025_API AScanSphereActor : public AActor
{
	GENERATED_BODY()
	
public:
    AScanSphereActor();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Detect")
    FTransform DetectedTargetTransform;
    UPROPERTY()
    class APlayerController* OwningPlayerController;

    UPROPERTY()
    class APawn* OriginalPawn;

    UPROPERTY(BlueprintAssignable)
    FOnTargetDetected OnTargetDetected;


    UPROPERTY(VisibleAnywhere)
    class USphereComponent* SphereComponent;

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
