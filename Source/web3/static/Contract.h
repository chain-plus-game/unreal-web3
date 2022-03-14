// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <web3/Public/keccak.h>
#include "Contract.generated.h"


USTRUCT()
struct FInitContract {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FString address;
	UPROPERTY()
		FString abi_url;
};

