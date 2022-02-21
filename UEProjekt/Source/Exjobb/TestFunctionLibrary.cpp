// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunctionLibrary.h"



FQuat UTestFunctionLibrary::EulerToQuatConverssion(FRotator eulerRotation)
{
	FQuat q;


	float yaw, pitch, roll;

	//convert degrees to radians since rotator deals in deegrees but we want radians
	yaw = (eulerRotation.Yaw * PI) / 180;
	pitch = (eulerRotation.Pitch * PI) / 180;
	roll = (eulerRotation.Roll * PI) / 180;

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);


	q.W = cr * cp * cy + sr * sp * sy;
	q.X = sr * cp * cy - cr * sp * sy;
	q.Y = cr * sp * cy + sr * cp * sy;
	q.Z = cr * cp * sy - sr * sp * cy;

	return q;
}

void UTestFunctionLibrary::AddActorLocalRotationQuat(AActor* Actor, const FQuat& deltaRotation)
{

	if (Actor) {
		Actor->AddActorLocalRotation(deltaRotation);
	}
}

void UTestFunctionLibrary::ApplyQuaternionRotation(AActor* Actor,  float inputAxis)
{

	FRotator rotator = FRotator(inputAxis, 0.f, 0.f);
	//FRotator currentRotator = FRotator(0.f, 0.f, 0.f);
	//Actor->GetActorRotation();
	
	
	FQuat currentRotation = Actor->GetActorQuat();
	
	FQuat DesiredRotationLeft = FQuat(FRotator(inputAxis, 0.f, 0.f));
	

	FQuat newQuat = FQuat::Slerp(currentRotation, DesiredRotationLeft, 0.5f);
	//FQuat newQuatInv = FQuat::Slerp(currentRotation, DesiredRotationRight, 0.5f);
	
	Actor->AddActorLocalRotation(newQuat);
	//if (inputAxis < 0) {
	//	Actor->SetActorRotation(newQuat);
	//}

	
}

FRotator UTestFunctionLibrary::ApplyQuaternionRotationComponent(USceneComponent* sceneComponent, float inputX, float inputY)
{
	float rotator = 0;

	bool isRotating = false;
	FQuat currentRot = FQuat(sceneComponent->USceneComponent::GetComponentRotation());

	FQuat DesiredRotationLeft = FQuat(FRotator(0.f, -inputX*0.2, -inputY*0.2));


	FQuat newQuat = FQuat::Slerp(currentRot, DesiredRotationLeft, 0.5f);


	if (inputX != 0 || inputY != 0) {
		//sceneComponent->SetWorldRotation(newQuat);
		//sceneComponent->SetRelativeRotation(newQuat);
		sceneComponent->AddLocalRotation(DesiredRotationLeft);
	}
	
	
	return newQuat.Rotator();
	
}

void UTestFunctionLibrary::ApplyQuaternionRotationForGrabbedObjects(USceneComponent* hitComponent, USceneComponent* motionController, FRotator initialRot)
{
	FRotator motionControllerRotation = motionController->GetComponentRotation();
	
	FQuat initialQuat = FQuat(initialRot);
	
	FQuat motionControllerQuatRot = FQuat(motionControllerRotation);

	FQuat newQuat = FQuat(motionControllerQuatRot.X*1.5f, motionControllerQuatRot.Y*1.5f, motionControllerQuatRot.Z*1.5f, motionControllerQuatRot.W);
	hitComponent->SetWorldRotation(newQuat);
}


void UTestFunctionLibrary::ApplyTeleportationRotationQuat(UCameraComponent* camera, FRotator arrowRotation, FRotator currentRotation)
{

	FQuat arrowQuat = FQuat(arrowRotation);
	FQuat currentQuat = FQuat(currentRotation);


	FQuat desiredQuat = arrowQuat*currentQuat;


	camera->SetWorldRotation(desiredQuat);

	
}

void UTestFunctionLibrary::DestroyActorOnButtonPress(AActor* Actor)
{
	if (Actor) {
		Actor->K2_DestroyActor();
	}
}

bool UTestFunctionLibrary::IsSelectable(AActor* actor)
{
	if (actor) {
		return true;
	}
	else
	{
		return false;
	}
}

void UTestFunctionLibrary::SetHighlight(UPrimitiveComponent* hitComponent)
{

	if (hitComponent){
		hitComponent->SetRenderCustomDepth(true);
		hitComponent->SetCustomDepthStencilValue(2.f);
	}
	
	
	
}

void UTestFunctionLibrary::DeleteHighlight(UPrimitiveComponent* hitComponent)
{
	if (hitComponent) {
		hitComponent->SetRenderCustomDepth(false);
		hitComponent->SetCustomDepthStencilValue(0.f);
	}
}

void UTestFunctionLibrary::RotateSelectionUMGWidget(USceneComponent* camera, USceneComponent* widget)
{

	FVector cameraPos = camera->GetComponentLocation();
	FVector widgetPos = widget->GetComponentLocation();

	FRotator firstRotation = UKismetMathLibrary::FindLookAtRotation( widgetPos, cameraPos);

	float yaw, pitch, roll;

	yaw = firstRotation.Yaw - 90.f;

	roll = 90.f;
	pitch = -90.f;

	FRotator targetRotation = FRotator(pitch, roll, yaw);
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %f - %f - %f"), targetRotation.Pitch, targetRotation.Yaw, targetRotation.Roll));

	widget->SetWorldRotation(targetRotation);
}

void UTestFunctionLibrary::SetSimulatePhysicsToValid(UPrimitiveComponent* comp)
{
	if (comp) {
		comp->SetSimulatePhysics(false);
	}
}

float UTestFunctionLibrary::SetInitialDistance(USceneComponent* LeftController, USceneComponent* RightController)
{
	FVector leftPos = LeftController->GetComponentLocation();
	FVector rightPos = RightController->GetComponentLocation();

	FVector distanceVec = leftPos - rightPos;

	float initialDistance = distanceVec.Size();
	
	return initialDistance;
	
}

FRotator UTestFunctionLibrary::GetObjectPlacementRotationFromNormal(FVector normal)
{

	float x = normal.X;
	float y = normal.Y;
	float z = normal.Z;
	FRotator outRotation = FRotator(); //initialize

	if (y < -0.5) {
		outRotation = FRotator(-90.f, -90.f, 0.f);
	}
	else if (y > 0.5) {
		outRotation = FRotator(90.f, -90.f, 0.f);
	}

	else if (x < -0.5) {
		outRotation = FRotator(-90.f, 90.f, 90.f);
		
	}
	else if (x > 0.5) {
		outRotation = FRotator(90.f, 180.f, 0.f);
	}
	else if (z > 0.5) {
		outRotation = FRotator(0.f, 180.f, 0.f);
	}

	return outRotation;
}

bool UTestFunctionLibrary::isDetachable(UPrimitiveComponent* comp)
{
	if (comp) {
		return true;
	}
	else {
		return false;
	}
}

bool UTestFunctionLibrary::isDetachableComponent(UPrimitiveComponent* comp)
{
	
	
	if (comp) {
		return true;
	}
	else {
		return false;
	}
	
}

float UTestFunctionLibrary::getFloatGrabDistance(UPrimitiveComponent* hitComp, USceneComponent* anchor)
{

	FVector hitCompPos = hitComp->GetComponentLocation();
	FVector anchorPos = anchor->GetComponentLocation();
	
	FVector distanceVec = hitCompPos - anchorPos;

	float initialDistance = distanceVec.Size();

	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Norm: %f - %f - %f"), distanceVec.X, distanceVec.Y, distanceVec.Z));

	return initialDistance;

}

float UTestFunctionLibrary::getFloatWandAnchorDistance(USceneComponent* wand, USceneComponent* anchor)
{

	FVector wandPos = wand->GetComponentLocation();
	FVector anchorPos = anchor->GetComponentLocation();

	FVector distanceVec = wandPos - anchorPos;

	float initialDistance = distanceVec.Size();

	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Norm: %f - %f - %f"), distanceVec.X, distanceVec.Y, distanceVec.Z));
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::Printf(TEXT("initwand dist:  %f"), initialDistance));

	return initialDistance;

}





FVector UTestFunctionLibrary::getAnchorUpdatedGrabLocation(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector initObjectPos, FVector initAnchorPos, FVector initWandPos)
{
	//vectors from anchor to wand and anchor to object
	FVector wandVec = wand->GetComponentLocation();
	FVector anchorVec = anchor->GetComponentLocation();
	

	//Init 
	FVector initAnchorObjectNorm = (initObjectPos - initAnchorPos).GetSafeNormal();
	FVector initAnchorWandNorm = (initWandPos - initAnchorPos).GetSafeNormal();

	float dotProd = FVector::DotProduct(initAnchorObjectNorm, initAnchorWandNorm);

	float angle = acos(dotProd);

	float l1 = (initWandPos - initAnchorPos).Size();
	float l2 = l1 * acos(angle);

	FVector a1 = initAnchorPos + (initObjectPos - initAnchorPos).GetSafeNormal() * l2;

	FVector wanda1diff = (a1 - initWandPos);
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::Printf(TEXT("Angle:  %f"), a1.X));
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Norm: %f - %f - %f"), a1.X, a1.Y, a1.Z));


	//FVector anchorWandVec = (wandVec + wanda1diff) - anchorVec;
	FVector anchorWandVec = wandVec - anchorVec;
	float magnitude = sqrt(anchorWandVec.X * anchorWandVec.X + anchorWandVec.Y * anchorWandVec.Y + anchorWandVec.Z * anchorWandVec.Z);
	FVector norm = anchorWandVec / magnitude;



	float a = (wandVec - anchorVec).Size();
	float r = anchorWandDist / anchorObjectDist;
	float A = a / r;

	

	FVector newPos = anchorVec + norm * A;
	

	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Norm: %f - %f - %f"), norm.X, norm.Y, norm.Z));
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::Printf(TEXT("A:  %f"), r));

	return newPos;
}


FVector UTestFunctionLibrary::getExArmObjectPos(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector initObjectPos, FVector initAnchorPos, FVector initWandPos)
{

	//vectors from anchor to wand and anchor to object
	FVector currentWandPos = wand->GetComponentLocation();
	FVector currentAnchorPos = anchor->GetComponentLocation();

	//Init 
	FVector c = (initObjectPos - initWandPos);
	FVector a = (initWandPos - initAnchorPos);

	//kj:s lösning
	float acDotProduct = FVector::DotProduct(a.GetSafeNormal(), c.GetSafeNormal());
	float phi = acos(acDotProduct);
	FVector rhat = FVector::CrossProduct(a, c).GetSafeNormal();// / FVector::CrossProduct(a, c).Size();

	FQuat Q = FQuat(rhat, phi);

	float r = c.Size() / a.Size();
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::Printf(TEXT("r:  %f"), a.Size() * c.Size()));
	
	FVector p = currentWandPos + Q.RotateVector(currentWandPos - currentAnchorPos) * r;
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("p: %f - %f - %f - %f"), Q.X, Q.Y, Q.Z, Q.W));
	
	return p;
}

FVector UTestFunctionLibrary::getHomerOffsetPos(UPrimitiveComponent* wand, USceneComponent* anchor, float anchorObjectDist, float anchorWandDist, FVector initObjectPos, FVector initAnchorPos, FVector initWandPos, FVector HitObjectWorldLocation)
{

	//current wand and anchor positions
	FVector currentWandPos = wand->GetComponentLocation();
	FVector currentAnchorPos = anchor->GetComponentLocation();


	//D and d and dCurr
	float D = (initObjectPos - initAnchorPos).Size();
	float d = (initWandPos - initAnchorPos).Size();
	float dCurr = (currentAnchorPos - currentWandPos).Size();
	float dvh = dCurr * (D / d);
	//Expected pos on grab
	FVector pe =  initAnchorPos +(initWandPos - initAnchorPos).GetSafeNormal() * D;
	//Offset poffset
	FVector pOffset = initObjectPos - pe;//pe - (D * (initWandPos - initAnchorPos) / d);
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Norm: %f - %f - %f"), pOffset.X, pOffset.Y, pOffset.Z));
	//desired pos pd
	FVector objectAdjust = HitObjectWorldLocation - initObjectPos;

	FVector pd = currentAnchorPos + pOffset+ dvh* (currentWandPos - currentAnchorPos)/dCurr;





	return pd;
}

FRotator UTestFunctionLibrary::getRandomRotation()
{
	TArray<FRotator> rotationArray;

	FRotator rot1 = FRotator(0,0,90);
	FRotator rot2 = FRotator(0, 90, 0);
	FRotator rot3 = FRotator(90, 0, 0);
	FRotator rot4 = FRotator(0, 0, 0);

	rotationArray.Insert(rot1, 0);
	rotationArray.Insert(rot2, 1);
	rotationArray.Insert(rot3, 2);
	rotationArray.Insert(rot4, 3);

	int rand = FMath::RandRange(0, 3);
	return rotationArray[rand];
}






