// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

	UPROPERTY()
		bool notJson = false;

	void init() {}

	FString GetMethod() {
		return method;
	}

	void decode(FString& outStr){}
};

USTRUCT()
struct FResBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		int id;
	UPROPERTY()
		FString jsonrpc;
};