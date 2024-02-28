// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpResponse.h"
#include "HTTPModule.h"
#include "CaptureUploader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUploadCompleted, bool, bSucceeded, FString, Message, FString, CheckoutURL);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnQRReceived, bool, bSucceeded, FString, Message, UTexture2D*, QRTexture, FString, CheckoutURL);

UCLASS()
class IGC_UE_API ACaptureUploader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaptureUploader();

	UPROPERTY(BlueprintAssignable, Category = "IGC")
		FOnUploadCompleted OnUploadCompleted;

	UPROPERTY(BlueprintAssignable, Category = "IGC")
		FOnQRReceived OnQRReceived;

	UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "UploadCaptures"))
		virtual void UploadCaptures(FString CaptureFolderPath, FString API_Key, TArray<FString> API_Mod, FString API_Scale = "", FString API_Notes = "");

	UFUNCTION(BlueprintCallable, Category = "IGC", meta = (Keywords = "UploadCaptures"))
		virtual void Checkout(FString CaptureFolderPath, FString CheckoutURL);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString BoundaryLabel = FString();
	FString BoundaryBegin = FString();
	FString BoundaryEnd = FString();

	FString AddData(FString Name, FString Value);

	FString GetBoundaryString(FString Name, FString FileName, FString Type);

	void OnUploadResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnCheckoutResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FString CheckoutURL);
};
