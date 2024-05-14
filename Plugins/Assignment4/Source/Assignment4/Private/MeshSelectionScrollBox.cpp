// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshSelectionScrollBox.h"

#define LOCTEXT_NAMESPACE "ScrollableAssetBoxWidget"

TSharedRef<SWidget> UMeshSelectionScrollBox::RebuildWidget()
{
	ScrollableAssetBox = SNew(SMeshSelectionScrollBox).InMeshDataAsset(MeshDataAsset).InThumbnailSize(ThumbnailSize);
	ScrollableAssetBox->OnMeshThumbnailSelected.BindUObject(this, &UMeshSelectionScrollBox::HandleAssetThumbnailSelected);
	ScrollableAssetBox->OnMaterialThumbnailSelected.BindUObject(this, &UMeshSelectionScrollBox::HandleAssetThumbnailSelected);
	ScrollableAssetBox->OnTextureThumbnailSelected.BindUObject(this, &UMeshSelectionScrollBox::HandleAssetThumbnailSelected);
	return ScrollableAssetBox.ToSharedRef();
}


const FText UMeshSelectionScrollBox::GetPaletteCategory()
{
	return LOCTEXT("PaletteCategory", "Panel");
}


void UMeshSelectionScrollBox::HandleAssetThumbnailSelected(const FMeshData& MeshData) {
	OnMeshAssetThumbnailSelected.Broadcast(MeshData);
}

void UMeshSelectionScrollBox::HandleAssetThumbnailSelected(const FMaterialData& MaterialData)
{
	OnMaterialAssetThumbnailSelected.Broadcast(MaterialData);
}

void UMeshSelectionScrollBox::HandleAssetThumbnailSelected(const FTextureData& TextureData)
{
	OnTextureAssetThumbnailSelected.Broadcast(TextureData);
}

void UMeshSelectionScrollBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (ScrollableAssetBox) {
		ScrollableAssetBox->ThumbnailSize = ThumbnailSize;
		ScrollableAssetBox->RefreshContent();
	}
}

#undef LOCTEXT_NAMESPACE