// Fill out your copyright notice in the Description page of Project Settings.


#include "MyReplayGameInstance.h"

UMyReplayGameInstance::UMyReplayGameInstance() {
	recordingName = "MyReplay";
	friendlyRecordingName = "MyReplay";
}

void UMyReplayGameInstance::startRecording()
{
	
	StartRecordingReplay(recordingName, friendlyRecordingName);
}

void UMyReplayGameInstance::stopRecording()
{
	StopRecordingReplay();

}

void UMyReplayGameInstance::startReplay()
{
	PlayReplay(recordingName, nullptr);
}
