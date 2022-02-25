// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include "Base.generated.h"

USTRUCT()
struct FReqBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		int id;
	UPROPERTY()
		FString method;
	UPROPERTY()
		FString jsonrpc = TEXT("2.0");

	void init() {}

	FString GetMethod() {
		return method;
	}
};

USTRUCT()
struct FResBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		int id;
	UPROPERTY()
		FString jsonrpc;

	void encode(FString& inStr) {
		FJsonObjectConverter::JsonObjectStringToUStruct(inStr, this, 0, 0);
	}
};