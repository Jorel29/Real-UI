// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCamera.h"

// Sets default values
AFPCamera::AFPCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	canMenuInteract = false;
	PC = Cast<APlayerController>(GetController());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::CenterScreen;
	WidgetInteractionComponent->SetupAttachment(CameraComponent);

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
	PlayerInputComponent->BindAxis("Pitch Axis", this, &AFPCamera::Pitch);

	PlayerInputComponent->BindAxis("Yaw Axis", this, &AFPCamera::Yaw);

	//Bind Menu Interact
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPCamera::MenuInteract);

}
void AFPCamera::Pitch(float Value)
{
	if (canMenuInteract) { return; }
	AddControllerPitchInput(Value);
}

void AFPCamera::Yaw(float Value) 
{
	if (canMenuInteract) { return; }
	AddControllerYawInput(Value);
}
void AFPCamera::MenuInteract() 
{
	CenterMouse(PC);
	FlipMenuInteract();
}

//Function that controls the Foward direction of the character
void AFPCamera::MoveForward(float Value)
{	
	if (canMenuInteract) { return; }
	FVector FVec = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(FVec, Value);
}

//Definition of Strafe left/right direction of the character
void AFPCamera::Strafe(float Value)
{
	if (canMenuInteract) { return; }
	FVector RVec = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(RVec, Value);
}

//Toggles boolean for menu interaction
void AFPCamera::FlipMenuInteract()
{
	if (canMenuInteract) {
		canMenuInteract = false;
		WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::CenterScreen;
	}
	else {
		canMenuInteract = true;
		WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;
	}
}

//need to implement for null values
void AFPCamera::CenterMouse(APlayerController* pc)
{
	ULocalPlayer* LocalPlayer = pc->GetLocalPlayer();

	FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;

	FVector2D ViewportSize;
	LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);

	const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
	const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

	Viewport->SetMouse(X, Y);

}

