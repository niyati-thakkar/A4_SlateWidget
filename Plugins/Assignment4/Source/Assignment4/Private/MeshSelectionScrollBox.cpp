// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshSelectionScrollBox.h"

#define LOCTEXT_NAMESPACE "ScrollableAssetBoxWidget"

TSharedRef<SWidget> UMeshSelectionScrollBox::RebuildWidget()
{
	ScrollableAssetBox = SNew(SMeshSelectionScrollBox).InMeshDataAsset(MeshDataAsset).InThumbnailSize(ThumbnailSize);
	ScrollableAssetBox->OnThumbnailSelected.BindUObject(this, &UMeshSelectionScrollBox::HandleAssetThumbnailSelected);
	return ScrollableAssetBox.ToSharedRef();
}


const FText UMeshSelectionScrollBox::GetPaletteCategory()
{
	return LOCTEXT("PaletteCategory", "Panel");
}


void UMeshSelectionScrollBox::HandleAssetThumbnailSelected(const FMeshData& MeshData) {
	OnAssetThumbnailSelected.Broadcast(MeshData);
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