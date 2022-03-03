// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <web3/Public/keccak.h>
#include "Contract.generated.h"

USTRUCT()
struct FInput {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		bool indexed;
	UPROPERTY()
		FName internalType;
	UPROPERTY()
		FString name;
	UPROPERTY()
		FName type;
};

USTRUCT()
struct FOutput {
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FName internalType;
	UPROPERTY()
		FName name;
	UPROPERTY()
		FName type;
};

USTRUCT()
struct FAbi {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		bool anonymous;

	UPROPERTY()
		FString name;

	UPROPERTY()
		TArray<FInput> inputs;

	UPROPERTY()
		TArray<FOutput> outputs;

	UPROPERTY()
		FName type;

	UPROPERTY()
		FName stateMutability;

};

USTRUCT()
struct FContractFunc {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		FString funcName;

	void decode(FString& outData) {}
	void encode(FString& inData) {}
	int paramNum() {
		return 0;
	}
};

USTRUCT()
struct FContract {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		TArray<FAbi> abi;

	void FuncHash(FString& _funcName, FString& funcHash, int paramsNum) {
		FString hashString = _funcName + TEXT("(");
		int abiIndex = -1;
		for (int i = 0; i < abi.Num(); i++)
		{
			if (abi[i].inputs.Num() == paramsNum && abi[i].name == _funcName) {
				abiIndex = i;
			}
		}
		check(abiIndex >= 0);
		for (int i = 0; i < abi[abiIndex].inputs.Num(); i++)
		{
			hashString += abi[abiIndex].inputs[i].name;
			if (i != abi[abiIndex].inputs.Num() - 1) {
				hashString += TEXT(",");
			}
		}
		hashString += TEXT(")");
		Keccak keccak(Keccak::Keccak256);
		keccak.add(TCHAR_TO_UTF8(*hashString), hashString.Len());
		funcHash = keccak.getHash().c_str();
	}
};