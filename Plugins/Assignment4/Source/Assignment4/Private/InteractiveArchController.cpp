// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveArchController.h"


void AInteractiveArchController::SpawnMesh(const FMeshData& MeshData)
{
	if (MeshData.Type) {
		FBox BoundingBox = MeshData.Type->GetBoundingBox();
		FVector MinBounds = BoundingBox.Min;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (AStaticMeshActor* MeshComponent = GetWorld()->SpawnActor<AStaticMeshActor>(LastHitLocation - MinBounds, FRotator(0), SpawnParameters)) {
			MeshComponent->SetMobility(EComponentMobility::Movable);
			MeshComponent->GetStaticMeshComponent()->SetStaticMesh(MeshData.Type);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("hello"));

}

void AInteractiveArchController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent)) {
		UInputMappingContext* IMC = NewObject<UInputMappingContext>();

		UInputAction* LeftClickAction = NewObject<UInputAction>();

		IMC->MapKey(LeftClickAction, EKeys::LeftMouseButton);

		EIC->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::GetMouseClick);
		const auto LocalPlayer = GetLocalPlayer();

		if (LocalPlayer)
		{
			if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				// Add the input mapping context to the local player subsystem
				SubSystem->AddMappingContext(IMC, 0);
			}
		}
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Crosshairs;

	}
}

void AInteractiveArchController::GetMouseClick(const FInputActionValue& InputAction) {
	float MouseX, MouseY;
	FVector WorldLocation, WorldDirection;
	if (GetMousePosition(MouseX, MouseY)) {
		if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
			FHitResult HitResult;
			FVector TraceEnd = WorldLocation + (WorldDirection * 10000.f);

			FCollisionQueryParams QueryParams;
			QueryParams.bTraceComplex = true;
			QueryParams.AddIgnoredActor(GetPawn());

			if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility, QueryParams)) {
				if (HitResult.GetActor()) {
					LastHitLocation = HitResult.Location;
					if (OverlayWidget && !OverlayWidget->IsInViewport()) {
						OverlayWidget->AddToViewport();
						OverlayWidget->InitializeWidget(MeshDataAsset);
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("overlay added"));
					}
					//OnFloorDetection();
				}
			}
		}
	}
}

void AInteractiveArchController::BeginPlay() {
	Super::BeginPlay();

	if (OverlayWidgetClass) {
		OverlayWidget = CreateWidget<UOverlayWidget>(this, OverlayWidgetClass);
		if (OverlayWidget) {
			OverlayWidget->MeshThumbnailDelegate.AddDynamic(this, &AInteractiveArchController::SpawnMesh);
			//OverlayWidget->MaterialThumbnailDelegate.AddDynamic(this, &AInteractiveArchController::SpawnMesh);
			//OverlayWidget->TextureThumbnailDelegate.AddDynamic(this, &AInteractiveArchController::SpawnMesh);
		}
	}
}
