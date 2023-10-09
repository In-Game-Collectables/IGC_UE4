// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptureUploader.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"

TArray<uint8> FStringToUint8(const FString& InString)
{
	TArray<uint8> OutBytes;

	if (InString.Len() > 0)
	{
		FTCHARToUTF8 Converted(*InString); // Converts to UTF8?
		OutBytes.Append(reinterpret_cast<const uint8*>(Converted.Get()), Converted.Length());
	}
	return OutBytes;
}

ACaptureUploader::ACaptureUploader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACaptureUploader::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACaptureUploader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACaptureUploader::UploadCaptures(FString CaptureFolderPath, FString API_Key, FString API_Scale)
{
	FString TransformFile = FPaths::Combine(CaptureFolderPath, TEXT("transforms.json"));
	FString ImageFolderPath = FPaths::Combine(CaptureFolderPath, TEXT("images"));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = (&FHttpModule::Get())->CreateRequest();
	Request->SetURL("https://platform.igc.studio/api/create");
	Request->SetVerb("POST");

	BoundaryLabel = FString(TEXT("------------------------")) + FString::FromInt(FMath::Rand());
	BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
	BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

	Request->SetHeader(TEXT("Content-Type"), FString(TEXT("multipart/form-data; boundary=")) + BoundaryLabel);
	Request->OnProcessRequestComplete().BindUObject(this, &ACaptureUploader::OnUploadResponseReceived);

	TArray<uint8> CombinedContent; // payload

	FString TransformBoundaryString = GetBoundaryString("transforms", "transforms.json", "text/json");
	TArray<uint8> TransformFileRawData;
	if (!FFileHelper::LoadFileToArray(TransformFileRawData, *TransformFile)) {
		UE_LOG(LogTemp, Error, TEXT("ERROR: %s"), *FString("transforms.json could not be found"));
		UE_LOG(LogTemp, Error, TEXT("%s"), *FString("Exiting"));

		OnUploadCompleted.Broadcast(false, "Error: transforms.json could not be found for upload.", "");
		return;
	}

	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *ImageFolderPath, *FString(".png"));
	TArray<uint8> ImageFileRawData;
	FString ImageSetBoundaryString = FString();
	FString FilePath;

	if (Files.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: %s"), *FString("images could not be found"));
		UE_LOG(LogTemp, Error, TEXT("%s"), *FString("Exiting"));
		OnUploadCompleted.Broadcast(false, "Error: Images to upload could not be found.", "");
		return;
	}

	for (FString file : Files)
	{
		FilePath = FPaths::Combine(ImageFolderPath, file);
		ImageSetBoundaryString = GetBoundaryString("image_set[]", file, "image/png");
		FFileHelper::LoadFileToArray(ImageFileRawData, *FilePath);

		CombinedContent.Append(FStringToUint8(ImageSetBoundaryString));
		CombinedContent.Append(ImageFileRawData);
	}

	CombinedContent.Append(FStringToUint8(TransformBoundaryString));
	CombinedContent.Append(TransformFileRawData);

	CombinedContent.Append(FStringToUint8(AddData("api_key", API_Key)));

	if (API_Scale != "")
	{
		CombinedContent.Append(FStringToUint8(AddData("api_scale_param", API_Scale)));
	}

	CombinedContent.Append(FStringToUint8(AddData("source", "UnrealEngine")));
	CombinedContent.Append(FStringToUint8(BoundaryEnd));

	Request->SetContent(CombinedContent);

	Request->ProcessRequest();
}

void ACaptureUploader::Checkout(FString CaptureFolderPath, FString CheckoutURL)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = (&FHttpModule::Get())->CreateRequest();
	Request->SetURL(CheckoutURL + "/qr");
	Request->SetVerb("GET");

	Request->OnProcessRequestComplete().BindUObject(this, &ACaptureUploader::OnCheckoutResponseReceived, CheckoutURL);
	Request->ProcessRequest();
}


FString ACaptureUploader::AddData(FString Name, FString Value)
{
	return FString(TEXT("\r\n")) + BoundaryBegin + FString(TEXT("Content-Disposition: form-data; name=\"")) + Name + FString(TEXT("\"\r\n\r\n")) + Value;
}

FString ACaptureUploader::GetBoundaryString(FString Name, FString FileName, FString Type)
{
	FString FileBoundaryString = FString(TEXT("\r\n"))
		+ BoundaryBegin
		+ FString(TEXT("Content-Disposition: form-data; name=\""))
		+ Name
		+ FString(TEXT("\"; filename=\""))
		+ FileName + "\"\r\n"
		+ "Content-Type: "
		+ Type
		+ FString(TEXT("\r\n\r\n"));
	return FileBoundaryString;
}

void ACaptureUploader::OnUploadResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//UE_LOG(LogTemp, Display, TEXT("Success: Uploaded Captures. Response: %s"), *Response->GetContentAsString());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Response->GetContentAsString());

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	FString temp = FString();
	FString order_path = FString();
	bool success = JsonObject->TryGetStringField("id", temp);
	if (success)
	{
		FString id = JsonObject->GetStringField("id");
		order_path = JsonObject->GetStringField("order_path");
		UE_LOG(LogTemp, Display, TEXT("id: %s"), *FString(id));

		FString message = "Success: Uploaded Captures. Reponse: " + Response->GetContentAsString() + ". Code: " + FString::FromInt(Response->GetResponseCode());
		OnUploadCompleted.Broadcast(success, message, order_path);
	}
	else
	{
		FString message = "Error: Uploaded Captures but could not retrieve Checkout URL. Reponse: " + Response->GetContentAsString() + ". Code: " + FString::FromInt(Response->GetResponseCode());
		OnUploadCompleted.Broadcast(success, message, order_path);
	}

}


void ACaptureUploader::OnCheckoutResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FString CheckoutURL)
{
	//UE_LOG(LogTemp, Display, TEXT("Response: %s"), *Response->GetContentAsString());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Response->GetContentAsString());
	TArray<uint8> RawImageData = Response->GetContent();

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	//IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); // deprecated?
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	UTexture2D* QRTexture;

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawImageData.GetData(), RawImageData.Num()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("QR retrieved successfully"));
		//UE_LOG(LogTemp, Display, TEXT("QR retrieved successfully"));

		const TArray<uint8>* uncompressedBGRA = NULL;
		TArray<uint8> uncompressedRGBA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, uncompressedRGBA))
		{
			QRTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
			QRTexture->MipGenSettings = TMGS_NoMipmaps;

			void* QRTextureData = QRTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(QRTextureData, uncompressedRGBA.GetData(), uncompressedRGBA.Num());

			QRTexture->PlatformData->Mips[0].BulkData.Unlock();

			QRTexture->UpdateResource();
			OnQRReceived.Broadcast(true, "Success: QR Code retrieved successfully", QRTexture, CheckoutURL);
		}
		else
		{
			OnQRReceived.Broadcast(false, "Error: Connected to API but could not retrieve QR Code", NULL, CheckoutURL);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Something went wrong while retrieving QR Code"));
		OnQRReceived.Broadcast(false, "Error: Connected to API but could not retrieve QR Code", NULL, CheckoutURL);
		//UE_LOG(LogTemp, Display, TEXT("Something went wrong while retrieving QR Code"));
	}
}

