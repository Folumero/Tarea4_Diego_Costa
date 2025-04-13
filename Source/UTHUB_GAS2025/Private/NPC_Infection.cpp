// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Infection.h"

// Sets default values
ANPC_Infection::ANPC_Infection()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Infection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Infection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_Infection::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

