// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_CharacterBase.h"

// Sets default values
AEntity_CharacterBase::AEntity_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEntity_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntity_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntity_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

