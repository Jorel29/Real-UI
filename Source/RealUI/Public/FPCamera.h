// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components\WidgetInteractionComponent.h"
#include "FPCamera.generated.h"

UCLASS()
class REALUI_API AFPCamera : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Move Forward Backward Function
	UFUNCTION()
	void MoveForward(float Value);

	//Move Left Right Function
	UFUNCTION()
	void Strafe(float Value);
	

	//Make the CameraComponent visible to Blueprints anywhere, declare CameraComponent Object
	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	//Make WidgetInteractable Component visible to Blueprints
	UPROPERTY(EditAnywhere, Category = "Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;
};
