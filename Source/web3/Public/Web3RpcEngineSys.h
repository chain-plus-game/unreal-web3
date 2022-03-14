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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContractInitSuccess, FString, contractAddress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWsServerCallBack, FString, funcName, FString, data, FString, message);

/**
 *
 */
UCLASS(Config = Web3, defaultconfig, meta = (DisplayName = "Web3Rpc"))
class WEB3_API UWeb3RpcEngineSys : public UEngineSubsystem
{
	GENERATED_BODY()

		UWeb3RpcEngineSys(const FObjectInitializer& obj);

	UPROPERTY(Config, EditAnywhere, Category = Settings)
		FString ETHRpcUrl;

	UPROPERTY(Config, EditAnywhere, Category = Settings)
		FString ServerURL;

	UPROPERTY(Config, EditAnywhere, Category = Settings)
		FString ServerProtocol;

	UPROPERTY()
		int rpcId;

	UPROPERTY()
		TArray<FString> _contractArray;

public:
	UPROPERTY()
		FJsonRpcCallBack rpcCallBack;

	UPROPERTY()
		FContractInitSuccess contractInitSuccess;

	UPROPERTY()
		FWsServerCallBack wsCallBack;

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

	template<typename T>
	void WsCall(FString funcName, T data) {
		FWsReqBase req;
		FString body;
		FJsonObjectConverter::UStructToJsonObjectString(T::StaticStruct(), &data, body, 0, 0);
		req.func = funcName;
		req.data = body;
		FString message;
		FJsonObjectConverter::UStructToJsonObjectString(T::StaticStruct(), &req, message, 0, 0);
		WsSend(message);
	}

	void DoReq(FString method, FString& req);
	void WsSend(FString& message);

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
		void InitContract(FString abiUrl, FString address);

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void OnInitContractCallback(FString funcName, FString data, FString message);

};
