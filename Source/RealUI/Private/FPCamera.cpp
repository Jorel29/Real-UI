// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCamera.h"

// Sets default values
AFPCamera::AFPCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"))
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

	//Bind the player input component to the "Move Forward/Back" Input (set in the Project Settings)
	PlayerInputComponent->BindAxis("Move Forward/Back", this, &AFPCamera::MoveForward);
	//Bind the player input component to the "Strafe Left/Right" Input (See Project Settings->Input)
	PlayerInputComponent->BindAxis("Strafe Left/Right", this, &AFPCamera::Strafe);

}

