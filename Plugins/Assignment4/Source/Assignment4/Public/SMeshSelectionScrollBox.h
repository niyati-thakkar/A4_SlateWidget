// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "MeshAssetManager.h"
#include "SlateOptMacros.h"
#include "MeshAssetManager.h"
#include "Styling/SlateBrush.h"
#include "Engine/Texture2D.h"
#include "Widgets/Input/SEditableTextBox.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FAssetThumbnailSelected, const FMeshData&);

class ASSIGNMENT4_API SMeshSelectionScrollBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMeshSelectionScrollBox)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<UMeshAssetManager>, InMeshDataAsset)
	SLATE_ARGUMENT(float, InThumbnailSize)
	SLATE_END_ARGS()


private:
	TSharedPtr<SScrollBox> ScrollBox;
	TSharedPtr<STextBlock> TextBox;

	TWeakObjectPtr<UMeshAssetManager> MeshDataAsset;

public:
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	float ThumbnailSize;

	void RefreshContent();

	template<typename T> void DisplayThumbnailText(TArray<T> DataArray);
	FAssetThumbnailSelected OnThumbnailSelected;

	AssetType AssetT;
};
