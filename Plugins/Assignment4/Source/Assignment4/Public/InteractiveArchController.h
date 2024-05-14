// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MeshAssetManager.h"
#include "Engine/StaticMeshActor.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "OverlayWidget.h"
#include "EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "InteractiveArchController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API AInteractiveArchController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SpawnMesh(const FMeshData& MeshData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widget")
	UMeshAssetManager* MeshDataAsset;

	UPROPERTY()
	FVector LastHitLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UOverlayWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UOverlayWidget* OverlayWidget;


	void SetupInputComponent();
	void GetMouseClick(const FInputActionValue& InputAction);
	void BeginPlay();
};
