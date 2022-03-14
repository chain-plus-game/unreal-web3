// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <web3/Public/keccak.h>
#include <web3/Static/Contract.h>
#include "ContractFunc.generated.h"


USTRUCT()
struct FERC20BalanceOf {

	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FString ownerAddress;

	FERC20BalanceOf() {
	};
};