// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <web3/Public/keccak.h>
#include <web3/Static/Contract.h>
#include "ContractFunc.generated.h"


USTRUCT()
struct FERC20BalanceOf :public FContractFunc {

	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FString ownerAddress;

	FERC20BalanceOf() {
		funcName = TEXT("balanceOf");
	};
	void decode(FString& outData) override {
		check(ownerAddress.Len() == 42);
		FString _address = ownerAddress.RightChop(2);
		// ²¹ 64-42 ¸öÁã
		outData += TEXT("000000000000000000000000");
		outData += _address;
	}
	int paramNum() override {
		return 1;
	}
};