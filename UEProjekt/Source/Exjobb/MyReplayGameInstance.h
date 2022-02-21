// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyReplayGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXJOBB_API UMyReplayGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public: 

		UMyReplayGameInstance();

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Replay")
			FString recordingName;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Replay")
			FString friendlyRecordingName;

		UFUNCTION(BlueprintCallable, Category = "Replay")
			void startRecording();
	
		UFUNCTION(BlueprintCallable, Category = "Replay")
			void stopRecording();

		UFUNCTION(BlueprintCallable, Category = "Replay")
			void startReplay();
};
