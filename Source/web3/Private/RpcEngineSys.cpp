﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcEngineSys.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include <web3/Static/Contract.h>

DEFINE_LOG_CATEGORY(Web3RPC);

URpcEngineSys::URpcEngineSys(const FObjectInitializer& obj) {
	ETHRpcUrl = TEXT("https://bsc-dataseed1.binance.org/");
}

void URpcEngineSys::DoReq(FString method, FString& req)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	//设置Header
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetVerb("POST");
	//设置请求地址
	HttpRequest->SetURL(ETHRpcUrl);
	UE_LOG(Web3RPC, Warning, TEXT("send req :%s"), *req);
	//设置请求发送的数据
	HttpRequest->SetContentAsString(req);
	// Http执行完成回调
	FHttpRequestCompleteDelegate& CompleteDelegate = HttpRequest->OnProcessRequestComplete();
	CompleteDelegate.BindLambda(
		[this, method](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
		{
			if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
			{
				return;
			}
			FString res = HttpResponse->GetContentAsString();
			UE_LOG(Web3RPC, Warning, TEXT("get req method :%s"), *method);
			UE_LOG(Web3RPC, Warning, TEXT("get res body :%s"), *res);
			if (this->rpcCallBack.IsBound()) {
				this->rpcCallBack.Broadcast(method, res);
			}
		}
	);

	// Http执行
	HttpRequest->ProcessRequest();
	rpcId++;
}

void URpcEngineSys::GetProtocolVersion()
{
}

void URpcEngineSys::GetBalance(FString& address)
{
	FReqEthGetBalance req = FReqEthGetBalance();
	req.init(address);
	CallRpc<FReqEthGetBalance>(req);
}

void URpcEngineSys::InitContract(FString contractName, FString abiUrl)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	//设置Header
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetVerb("GET");
	//设置请求地址
	HttpRequest->SetURL(abiUrl);
	UE_LOG(Web3RPC, Warning, TEXT("begin to get %s abi :%s"), *contractName, *abiUrl);
	// Http执行完成回调
	FHttpRequestCompleteDelegate& CompleteDelegate = HttpRequest->OnProcessRequestComplete();
	CompleteDelegate.BindLambda(
		[this, &contractName](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
		{
			if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
			{
				UE_LOG(Web3RPC, Error, TEXT("Abi Get Error: %s"), *contractName);
				return;
			}
			UE_LOG(Web3RPC, Warning, TEXT("get %s Abi"), *contractName);

			FString res = HttpResponse->GetContentAsString();
			FContract contract;
			FJsonObjectConverter::JsonObjectStringToUStruct(res, &contract, 0, 0);
			if (this->_contractMap.Contains(contractName)) {
				this->_contractMap[contractName] = contract;
			}
			else {
				this->_contractMap.Add(contractName, contract);
			}
			if (this->contractInitSuccess.IsBound()) {
				this->contractInitSuccess.Broadcast(contractName);
			}
		}
	);

	// Http执行
	HttpRequest->ProcessRequest();
}

void URpcEngineSys::CallContractFunc(FString contractName, FContractFunc& contractFunc)
{
	check(_contractMap.Contains(contractName));
	FContract _contract = _contractMap[contractName];
	FString hash;
	_contract.FuncHash(contractName, hash, contractFunc.paramNum());
	UE_LOG(Web3RPC, Warning, TEXT("call to %s func, hash is %s"), *contractName, *hash);
}
