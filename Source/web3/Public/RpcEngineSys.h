// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include <web3/Static/Base.h>
#include <web3/Static/TypeStructure.h>
#include "RpcEngineSys.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJsonRpcCallBack, FString, funcName, FString, res);
/**
 *
 */
UCLASS(Config = Web3)
class WEB3_API URpcEngineSys : public UEngineSubsystem
{
	GENERATED_BODY()

	URpcEngineSys(const FObjectInitializer& obj);

	UPROPERTY(Config)
		FString ETHRpcUrl;

	UPROPERTY()
		int rpcId;

public:
	FJsonRpcCallBack rpcCallBack;

private:
	
	template<typename T>
	void CallRpc(T req) {
		req.id = rpcId;
		FString body;
		FJsonObjectConverter::UStructToJsonObjectString(T::StaticStruct(), &req, body, 0, 0);
		FString method = req.GetMethod();
		DoReq(method, body);
	}

	void DoReq(FString method, FString& req);

public:

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void GetProtocolVersion();

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void GetBalance(FString& address);
};
