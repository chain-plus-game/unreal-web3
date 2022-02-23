// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcEngineSys.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

void URpcEngineSys::GetProtocolVersion()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	//设置Header
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetVerb("POST");
	//设置请求地址
	HttpRequest->SetURL(ETHRpcUrl);
	//设置请求发送的数据
	HttpRequest->SetContentAsString(TEXT(""));
	// Http执行完成回调
	FHttpRequestCompleteDelegate& CompleteDelegate = HttpRequest->OnProcessRequestComplete();
	CompleteDelegate.BindLambda(
		[](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
		{
			if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
			{
				return;
			}
		}
	);

	// Http执行
	HttpRequest->ProcessRequest();
}
