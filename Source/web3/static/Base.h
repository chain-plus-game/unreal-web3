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
		FString jsonrpc = TEXT('2.0');

	void decode(FString& outStr) {
		FJsonObjectConverter::UStructToJsonObjectString(&this::StaticStruct(), this, outStr, 0, 0);
	}
};

USTRUCT()
struct FResBase{
	UPROPERTY()
		int id;
	UPROPERTY()
		FString jsonrpc;

	static FResBase encode(const FString& inStr){
		FResBase msgStruct;
		FJsonObjectConverter::JsonObjectStringToUStruct(inStr, &msgStruct, 0, 0);
		return msgStruct;
	} 	
}