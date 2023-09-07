// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "CaptureInformation.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct IGC_UE_API FFrameInformation
{
	GENERATED_BODY()

public: 
	FFrameInformation();
	FFrameInformation(FString fp, float s, FMatrix tm);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		FString file_path;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float sharpness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		FMatrix transform_matrix;
};

USTRUCT(BlueprintType)
struct IGC_UE_API FCaptureInformation
{
	GENERATED_BODY()

public:
	FCaptureInformation();
	FCaptureInformation(float caX, float caY, float flX, float flY, float w, float h);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float camera_angle_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float camera_angle_y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float fl_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float fl_y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float k1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float k2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float p1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float p2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float cx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float cy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float w;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		float h;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		int aabb_scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IGC")
		TArray<FFrameInformation> frames;
};
