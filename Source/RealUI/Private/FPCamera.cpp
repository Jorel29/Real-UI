// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCamera.h"

// Sets default values
AFPCamera::AFPCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>()
}

// Called when the game starts or when spawned
void AFPCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

