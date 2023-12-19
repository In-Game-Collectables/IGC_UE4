// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "IGC_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class IGC_UE_API UIGC_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:


		UFUNCTION(BlueprintPure, Category = "IGC", meta = (Keywords = "LoadJson"))
			static bool LoadJson(FString FileNameA, FString& SaveTextA);

		UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "SaveJson"))
			static bool SaveJson(FString SaveTextB, FString FileNameB);

		UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "SaveCapture"))
			static void SaveCaptureInformationToJSON(FString FileNameA, FCaptureInformation CaptureInfo);

		UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "DeleteAllCaptures"))
			static void DeleteAllCaptures(FString FolderPath);

		UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "DeleteCapture"))
			static void DeleteCapture(FString FilePath);

		UFUNCTION(BlueprintPure, Category = "IGC", meta = (Keywords = "GetAndroidCapturePath"))
			static FString GetAndroidCapturePath();
};

