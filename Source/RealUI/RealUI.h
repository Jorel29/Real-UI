// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

//Viewport Size
const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

//Viewport Center!            
const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);