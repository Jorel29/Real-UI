// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCamera.generated.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

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

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
