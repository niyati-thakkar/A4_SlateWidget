// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeshAssetManager.h"
#include "MeshSelectionScrollBox.h"
#include "OverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API UOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void InitializeWidget(UMeshAssetManager* MeshDataAsset);
	//UFUNCTION(BlueprintAssignableEvent)
	UPROPERTY(BlueprintAssignable, Category = "Overlay Widget")
	FMeshAssetThumbnailSelectedEvent MeshThumbnailDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Overlay Widget")
	FMaterialAssetThumbnailSelectedEvent MaterialThumbnailDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Overlay Widget")
	FTextureAssetThumbnailSelectedEvent TextureThumbnailDelegate;


	UFUNCTION(BlueprintCallable, Category = "Overlay Widget")
	void ReceiveMeshData(FMeshData MeshData);

	void ReceiveMeshData(FMaterialData MaterialData);

	void ReceiveMeshData(FTextureData TexureData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnMeshDataInitialization(const UMeshAssetManager* MeshDataAsset);
};
