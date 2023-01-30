// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCamera.h"

// Sets default values
AFPCamera::AFPCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::CenterScreen;
}

// Called when the game starts or when spawned
void AFPCamera::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCameraClass."));
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

	//Pitch Axis Bindings
	PlayerInputComponent->BindAxis("Pitch Axis", this, &AFPCamera::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Yaw Axis", this, &AFPCamera::AddControllerYawInput);
}

//Function that controls the Foward direction of the character
void AFPCamera::MoveForward(float Value)
{	
	FVector FVec = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(FVec, Value);
}

//Definition of Strafe left/right direction of the character
void AFPCamera::Strafe(float Value)
{
	FVector RVec = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(RVec, Value);
}


