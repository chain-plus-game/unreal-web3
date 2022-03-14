// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include <web3/Static/Base.h>
#include "TypeStructure.generated.h"

#define status_success "success"

#define wsfunc_init_contract "init_contract"
#define wsfunc_call "call"

#define eth_protocolVersion "eth_protocolVersion"
#define eth_getBalance "eth_getBalance"
#define eth_call "eth_call"

USTRUCT()
struct FReqEthGetBalance : public FReqBase {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		TArray<FString> params;

	FReqEthGetBalance() {
		method = eth_getBalance;
	}

	void init(FString& address) {
		params.Add(address);
		params.Add(TEXT("latest"));
	}
};

USTRUCT()
struct FResEthGetBalance : public FResBase {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		FString result;
};

USTRUCT()
struct FTransactionCall {
	GENERATED_USTRUCT_BODY()
public:
	FString from;
	FString to;
	int gas;
	int gasPrice;
	int value;
	FString data;
};

USTRUCT()
struct FReqEthCall : public FReqBase {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		TArray<FString> params;

	FReqEthCall() {
		method = eth_call;
		notJson = true;
	}

	void init(FString& fromAddress, FString& toAddress, FString& data) {
		FTransactionCall callData;
		callData.from = fromAddress;
		callData.to = toAddress;
		callData.data = data;
		params.Add(TEXT("latest"));
	}
	void decode(FString& outStr) {

	}
};


USTRUCT()
struct FWsResBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		FString callBack;

	UPROPERTY()
		FString data;

	UPROPERTY()
		FString messsag;
};

USTRUCT()
struct FWsReqBase {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		FString func;

	UPROPERTY()
		FString data;

	UPROPERTY()
		FString messsag;
};

USTRUCT()
struct FWsInitContract {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		FString address;

	UPROPERTY()
		FString abi_url;
};
