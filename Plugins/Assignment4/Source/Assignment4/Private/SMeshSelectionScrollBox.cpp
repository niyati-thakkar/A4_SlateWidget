// Fill out your copyright notice in the Description page of Project Settings.


#include "SMeshSelectionScrollBox.h"




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMeshSelectionScrollBox::Construct(const FArguments& InArgs)
{
	MeshDataAsset = InArgs._InMeshDataAsset;
	ThumbnailSize = InArgs._InThumbnailSize;

	ScrollBox = SNew(SScrollBox);
	TextBox = SNew(STextBlock)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 24))
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Black);

    ChildSlot
        [
            ScrollBox.ToSharedRef()
        ];

	ScrollBox->SetOrientation(Orient_Horizontal);
	AssetT = AssetType::MeshType;
	RefreshContent();
}
void SMeshSelectionScrollBox::RefreshContent()
{

	ScrollBox->ClearChildren();
	if (MeshDataAsset.IsValid()) {

		//if (AssetT == AssetType::MeshType) {
			DisplayMeshes(MeshDataAsset->MeshDataArray);
		//}
		//if (AssetT == AssetType::MaterialType) {
			DisplayMaterials(MeshDataAsset->MaterialDataArray);
		//}
		//if (AssetT == AssetType::TextureType) {
			DisplayTextures(MeshDataAsset->TextureDataArray);
		//}
		
	}
}


void SMeshSelectionScrollBox::DisplayTextures(TArray<FTextureData> DataArray)
{
	for (const FTextureData& Data : DataArray) {
		if (Data.Type) {
			if (UTexture2D* ThumbnailTexture = Cast<UTexture2D>(Data.Type)) {
				FSlateBrush* SlateBrush = new FSlateBrush();
				SlateBrush->SetResourceObject(Data.Type);
				SlateBrush->ImageSize = FVector2D(ThumbnailSize, ThumbnailSize);
				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(SlateBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda([this, Data](const FGeometry& MouseGeometry, const FPointerEvent& MouseEvent) {
					if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
						OnTextureThumbnailSelected.ExecuteIfBound(Data);
						return FReply::Handled();
					}
					return FReply::Unhandled();
						});

				TextBox->SetText(Data.Name);

				ScrollBox->AddSlot()
					[
						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								ThumbnailImage.ToSharedRef()
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								TextBox.ToSharedRef()
							]
					];

			}
		}
	}
}

void SMeshSelectionScrollBox::DisplayMaterials(TArray<FMaterialData> DataArray)
{
	for (const FMaterialData& Data : DataArray) {
		if (Data.Type) {
			if (UTexture2D* ThumbnailTexture = Cast<UTexture2D>(Data.Icon)) {
				FSlateBrush* SlateBrush = new FSlateBrush();
				SlateBrush->SetResourceObject(Data.Icon);
				SlateBrush->ImageSize = FVector2D(ThumbnailSize, ThumbnailSize);
				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(SlateBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda([this, Data](const FGeometry& MouseGeometry, const FPointerEvent& MouseEvent) {
					if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
						OnMaterialThumbnailSelected.ExecuteIfBound(Data);
						return FReply::Handled();
					}
					return FReply::Unhandled();
						});

				TextBox->SetText(Data.Name);

				ScrollBox->AddSlot()
					[
						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								ThumbnailImage.ToSharedRef()
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								TextBox.ToSharedRef()
							]
					];
			}


		}
	}
}

void SMeshSelectionScrollBox::DisplayMeshes(TArray<FMeshData> DataArray)
{
	for (const FMeshData& Data : DataArray) {
		if (Data.Type) {
			if (UTexture2D* ThumbnailTexture = Cast<UTexture2D>(Data.Icon)) {
				FSlateBrush* SlateBrush = new FSlateBrush();
				SlateBrush->SetResourceObject(Data.Icon);
				SlateBrush->ImageSize = FVector2D(ThumbnailSize, ThumbnailSize);
				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(SlateBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda([this, Data](const FGeometry& MouseGeometry, const FPointerEvent& MouseEvent) {
					if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
						OnMeshThumbnailSelected.ExecuteIfBound(Data);
						return FReply::Handled();
					}
					return FReply::Unhandled();
						});

				TextBox->SetText(Data.Name);

				ScrollBox->AddSlot()
					[
						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								ThumbnailImage.ToSharedRef()
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								TextBox.ToSharedRef()
							]
					];
			}


		}
	}
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
