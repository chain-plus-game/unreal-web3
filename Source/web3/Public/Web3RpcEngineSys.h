// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include <web3/Static/Base.h>
#include <web3/Static/TypeStructure.h>
#include <web3/Static/Contract.h>
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Web3RpcEngineSys.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Web3RPC, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJsonRpcCallBack, FString, funcName, FString, res);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContractInitSuccess, FString, contractName);

/**
 *
 */
UCLASS(Config = Web3)
class WEB3_API UWeb3RpcEngineSys : public UEngineSubsystem
{
	GENERATED_BODY()

		UWeb3RpcEngineSys(const FObjectInitializer& obj);

	UPROPERTY(Config)
		FString ETHRpcUrl;

	UPROPERTY()
		int rpcId;

	UPROPERTY()
		TMap<FString, FContract> _contractMap;

public:
	UPROPERTY()
		FJsonRpcCallBack rpcCallBack;

	UPROPERTY()
		FContractInitSuccess contractInitSuccess;

	TSharedPtr<IWebSocket> Socket = nullptr;
private:

	template<typename T>
	void CallRpc(T req) {
		req.id = rpcId;
		FString body;
		if (req.notJson) {
			req.decode(body);
		}
		else {
			FJsonObjectConverter::UStructToJsonObjectString(T::StaticStruct(), &req, body, 0, 0);
		}
		FString method = req.GetMethod();
		DoReq(method, body);
	}

	void DoReq(FString method, FString& req);

protected:

	void OnConnected();
	void OnConnectionError(const FString& Error);
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnMessage(const FString& Message);
	void OnMessageSent(const FString& MessageString); 

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void GetProtocolVersion();

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void GetBalance(FString& address);

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void InitContract(FString contractName, FString abiUrl);

	UFUNCTION()
		void CallContractFunc(FString contractName, FContractFunc& contractFunc);


};
