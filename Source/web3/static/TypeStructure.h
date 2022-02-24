// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include <static/TypeStructure.h>
#include "TypeStructure.generated.h"


USTRUCT()
struct FReqEthGetBalance: public FReqBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		int id;
	UPROPERTY()
		FString method = TEXT('eth_getBalance');

    UPROPERTY()
        TArray<FString> params;
    
    void init(FString& address) {
		params.Add(address);
        params.Add(TEXT('latest'));
	}
};