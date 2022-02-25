// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcEngineSys.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

URpcEngineSys::URpcEngineSys(const FObjectInitializer& obj) {
	ETHRpcUrl = TEXT("https://bsc-dataseed1.binance.org/");
}

void URpcEngineSys::DoReq(FString method,FString& req)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	//设置Header
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetVerb("POST");
	//设置请求地址
	HttpRequest->SetURL(ETHRpcUrl);
	UE_LOG(LogTemp, Warning, TEXT("send req :%s"), *req);
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
			UE_LOG(LogTemp, Warning, TEXT("get req method :%s"), *method);
			UE_LOG(LogTemp, Warning, TEXT("get res body :%s"), *res);
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
