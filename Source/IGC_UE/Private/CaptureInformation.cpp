// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureInformation.h"

FFrameInformation::FFrameInformation()
{
	file_path = "";
	sharpness = 0.0;
	transform_matrix = FMatrix();
}

FFrameInformation::FFrameInformation(FString fp, float s, FMatrix tm)
{
	file_path = fp;
	sharpness = s;
	transform_matrix = tm;
}

FCaptureInformation::FCaptureInformation()
{
	camera_angle_x = 0.0;
	camera_angle_y = 0.0;
	fl_x = 0.0;
	fl_y = 0.0;
	k1 = 0.0;
	k2 = 0.0;
	p1 = 0.0;
	p2 = 0.0;
	cx = 0.0;
	cy = 0.0;
	w = 0.0;
	h = 0.0;
	aabb_scale = 0;
}

FCaptureInformation::FCaptureInformation(float caX, float caY, float flX, float flY, float width, float height)
{
	camera_angle_x = caX;
	camera_angle_y = caY;
	fl_x = flX;
	fl_y = flY;
	k1 = 0.0;
	k2 = 0.0;
	p1 = 0.0;
	p2 = 0.0;
	cx = 0.0;
	cy = 0.0;
	w = width;
	h = height;
	aabb_scale = 0;
}