// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/Quat.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "Containers/Array.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/UnrealString.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Math/TransformNonVectorized.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXJOBB_API UTestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintPure, Category = "Rotation category")
			static FQuat EulerToQuatConverssion(FRotator eulerRotation);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static void AddActorLocalRotationQuat(AActor* Actor, const FQuat &ActorRotation);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static void ApplyQuaternionRotation(AActor* Actor, float inputAxis);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static FRotator ApplyQuaternionRotationComponent(USceneComponent* sceneComponent, float inputX, float inputY);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static void ApplyQuaternionRotationForGrabbedObjects(USceneComponent* hitComponent, USceneComponent* motionController, FRotator initialRot);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static void ApplyTeleportationRotationQuat(UCameraComponent* camera, FRotator arrowRotation,FRotator currentRotation);

		UFUNCTION(BlueprintCallable, Category = "Rotation category")
			static void DestroyActorOnButtonPress(AActor* Actor);
		

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static bool IsSelectable(AActor* actor);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static void SetHighlight(UPrimitiveComponent* hitComponent);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static void DeleteHighlight(UPrimitiveComponent* hitComponent);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static void RotateSelectionUMGWidget(USceneComponent* camera, USceneComponent* widget);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static void SetSimulatePhysicsToValid(UPrimitiveComponent* comp);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static float SetInitialDistance(USceneComponent* LeftController, USceneComponent* RightController);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static FRotator GetObjectPlacementRotationFromNormal(FVector normal);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static bool isDetachable(UPrimitiveComponent* comp);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static bool isDetachableComponent(UPrimitiveComponent* comp);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static float getFloatGrabDistance(UPrimitiveComponent* hitComp, USceneComponent* anchor);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static FVector getAnchorUpdatedGrabLocation(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector currentObjectPos, FVector currentAnchorPos, FVector currentWandPos);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static float getFloatWandAnchorDistance(USceneComponent* wand, USceneComponent* anchor);

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static FVector getExArmObjectPos(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector initObjectPos, FVector initAnchorPos, FVector initWandPos);
		

		UFUNCTION(BlueprintCallable, Category = "Custom category")
			static FVector getHomerOffsetPos(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector initObjectPos, FVector initAnchorPos, FVector initWandPos, FVector HitObjectWorldLocation);


		UFUNCTION(BlueprintPure, Category = "Custom category")
			static FRotator getRandomRotation();
};
