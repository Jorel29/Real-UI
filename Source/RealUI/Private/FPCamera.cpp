// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCamera.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AFPCamera::AFPCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	canMenuInteract = false;
	zoom = false;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetFieldOfView(90.0f);
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::CenterScreen;
	WidgetInteractionComponent->SetupAttachment(CameraComponent);

}

// Called when the game starts or when spawned
void AFPCamera::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	if (PC) {
		LP = PC->GetLocalPlayer();
	}
	if (LP) {
		Viewport = LP->ViewportClient->Viewport;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCameraClass.cpp"));
}

// Called every frame
void AFPCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(zoom)

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
	PlayerInputComponent->BindAction("InteractMode", IE_Pressed, this, &AFPCamera::MenuInteract);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AFPCamera::ZoomOnCursorPress);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AFPCamera::ZoomOnCursorRelease);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPCamera::PointerPress);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AFPCamera::PointerRelease);
}
void AFPCamera::Pitch(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Val: %f"), Value));
	if (!canMenuInteract != !zoom) { return; }
	if (zoom)
		AddControllerPitchInput(0.0 * Value);
	else
		AddControllerPitchInput(Value);
}

void AFPCamera::Yaw(float Value) 
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Value: %f"), Value));
	if (!canMenuInteract != !zoom) { return; }
	if (zoom)
		AddControllerYawInput(0.0 * Value);
	else
		AddControllerYawInput(Value);
}

void AFPCamera::PointerPress(FKey key) 
{
	WidgetInteractionComponent->PressPointerKey(key);
}

void AFPCamera::PointerRelease(FKey key)
{
	WidgetInteractionComponent->ReleasePointerKey(key);
}

void AFPCamera::ZoomOnCursorPress() 
{
	zoom = true;
	float X;
	float Y;
	float Z;
	FTransform actorTransform = GetActorTransform();
	FVector Forward = GetActorForwardVector();
	FVector mouseLocation;
	FVector mouseDirection;
	FVector mouseDirectionLocalSpace;
	FVector viewLocation;
	FVector viewDirection;
	FVector viewDirectionLocalSpace;
	FRotator controllerRot = PC->GetControlRotation();
	FVector2D Screen;

	LP->ViewportClient->GetViewportSize(Screen);
	if (!PC->DeprojectScreenPositionToWorld(Screen.X, Screen.Y, viewLocation, viewDirection))return;
	if (!PC->DeprojectMousePositionToWorld(mouseLocation, mouseDirection)) return;
	mouseDirectionLocalSpace = UKismetMathLibrary::InverseTransformDirection(actorTransform, mouseDirection);
	viewDirectionLocalSpace = UKismetMathLibrary::InverseTransformDirection(actorTransform, viewDirection);
	X = FMath::RadiansToDegrees(acosf(FVector::DotProduct(FVector(1,0,0), FVector(mouseDirectionLocalSpace.X, 0, 0))));
	Y = FMath::RadiansToDegrees(acosf(FVector::DotProduct(FVector(0,1,0), FVector(0, mouseDirectionLocalSpace.Y, 0))));
	Z = FMath::RadiansToDegrees(acosf(FVector::DotProduct(FVector(0,0,1), FVector(0, 0, mouseDirectionLocalSpace.Z))));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, controllerRot.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("X: %f,Y: %f, Z: %f"), X, Y-90, -1*(Z-90)));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, viewDirectionLocalSpace.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, mouseDirectionLocalSpace.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, Forward.ToString());
	//FMath::RInterpTo(originRotation, targetRotation, FApp::GetDeltaTime(), 5.0f);
	PC->SetControlRotation(controllerRot.Add(-1*(Z-90), -1 * (Y - 90), 0));
	CameraComponent->SetFieldOfView(90.0f);
}

void AFPCamera::ZoomOnCursorRelease() 
{
	zoom = false;
	CameraComponent->SetFieldOfView(90.0f);
}
void AFPCamera::MenuInteract() 
{
	CenterMouse(PC);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("X: %d, Y: %d"), Viewport->GetMouseX(), Viewport->GetMouseY()));
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
		PC->SetShowMouseCursor(false);
	}
	else {
		canMenuInteract = true;
		WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;
		PC->SetShowMouseCursor(true);
	}
}

//need to implement for null values
void AFPCamera::CenterMouse(APlayerController* pc)
{
	
	FVector2D ViewportSize;
	LP->ViewportClient->GetViewportSize(ViewportSize);

	const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
	const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

	PC->SetMouseLocation(X, Y);
}

