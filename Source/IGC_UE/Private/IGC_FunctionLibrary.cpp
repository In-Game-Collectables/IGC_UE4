// Fill out your copyright notice in the Description page of Project Settings.


#include "IGC_FunctionLibrary.h"
#include "IGC_UE.h"
#include "CaptureInformation.h"



bool UIGC_FunctionLibrary::LoadJson(FString FileNameA, FString& SaveTextA)
{
    TSharedPtr<FJsonObject> obj;
    FString JsonString;
    TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(JsonString);

    FCaptureInformation info;

    if (FJsonSerializer::Deserialize(reader, obj)) {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, JsonString);
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Working now");
        }
    }
    else {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "ERROR");
        }
    }

    return FFileHelper::LoadFileToString(SaveTextA, *(FileNameA));
}

bool UIGC_FunctionLibrary::SaveJson(FString SaveTextB, FString FileNameB)
{
    return FFileHelper::SaveStringToFile(SaveTextB, *(FileNameB));
}


void UIGC_FunctionLibrary::SaveCaptureInformationToJSON(FString FileNameA, FCaptureInformation CaptureInfo) 
{
    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(CaptureInfo, JsonString, 0, 0);

#ifdef USE_ANDROID_FILE
    extern FString GInternalFilePath;
    FFileHelper::SaveStringToFile(JsonString, *(GInternalFilePath + "/transforms.json"));
#else
    FFileHelper::SaveStringToFile(JsonString, *(FileNameA));
#endif
    return;
}

void UIGC_FunctionLibrary::DeleteAllCaptures(FString FolderPath)
{
#ifndef USE_ANDROID_FILE
    TArray<FString> Files;
    IFileManager::Get().FindFiles(Files, *FolderPath, TEXT(".png"));

    for (FString file : Files)
    {
        FString imagePath = FolderPath + file;
        DeleteCapture(imagePath);
    }
#endif
}

void UIGC_FunctionLibrary::DeleteCapture(FString FilePath)
{
    if (!FilePath.IsEmpty())
    {
        if (FPaths::ValidatePath(FilePath) && FPaths::FileExists(FilePath)) {
            IFileManager& FileManager = IFileManager::Get();
            FileManager.Delete(*FilePath);
        }
    }
}

FString UIGC_FunctionLibrary::GetAndroidCapturePath()
{
#ifdef USE_ANDROID_FILE
    extern FString GInternalFilePath;
    return GInternalFilePath;
#else
    return "";
#endif

}

