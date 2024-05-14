// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidget.h"

#include "OverlayWidget.h"

void UOverlayWidget::InitializeWidget(UMeshAssetManager* MeshDataAsset)
{
	OnMeshDataInitialization(MeshDataAsset);
}

void UOverlayWidget::ReceiveMeshData(FMeshData MeshData)
{
	MeshThumbnailDelegate.Broadcast(MeshData);
}

void UOverlayWidget::ReceiveMeshData(FMaterialData MaterialData)
{
	MaterialThumbnailDelegate.Broadcast(MaterialData);
}

void UOverlayWidget::ReceiveMeshData(FTextureData TextureData)
{
	TextureThumbnailDelegate.Broadcast(TextureData);
}
