// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3RpcEngineSys.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include <web3/Static/Contract.h>

DEFINE_LOG_CATEGORY(Web3RPC);

UWeb3RpcEngineSys::UWeb3RpcEngineSys(const FObjectInitializer& obj) {
	ETHRpcUrl = TEXT("https://bsc-dataseed1.binance.org/");
	ServerURL = TEXT("ws://127.0.0.1:5000");
	ServerProtocol = TEXT("ws");
}

void UWeb3RpcEngineSys::Initialize(FSubsystemCollectionBase& Collection) {
	FModuleManager::Get().LoadModuleChecked("WebSockets");
	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);
	this->wsCallBack.AddDynamic(this, &UWeb3RpcEngineSys::OnInitContractCallback);
}

void UWeb3RpcEngineSys::DoReq(FString method, FString& req)
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

void UWeb3RpcEngineSys::OnConnected()
{
	UE_LOG(Web3RPC, Warning, TEXT("connect to %s"), *ServerURL);
}

void UWeb3RpcEngineSys::OnConnectionError(const FString& Error)
{
	UE_LOG(Web3RPC, Warning, TEXT("connect error %s"), *Error);
}

void UWeb3RpcEngineSys::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	UE_LOG(Web3RPC, Warning, TEXT("web socket close %d"), StatusCode);
}

void UWeb3RpcEngineSys::OnMessage(const FString& Message)
{
	UE_LOG(Web3RPC, Display, TEXT("on message %s"), *Message);
	FWsResBase data;
	FJsonObjectConverter::JsonObjectStringToUStruct(Message, &data, 0, 0);
	if (this->wsCallBack.IsBound()) {
		this->wsCallBack.Broadcast(data.callBack, data.data, data.messsag);
	}
}

void UWeb3RpcEngineSys::OnMessageSent(const FString& MessageString)
{
	UE_LOG(Web3RPC, Display, TEXT("on message sent %s"), *MessageString);
}

void UWeb3RpcEngineSys::WsSend(FString& message)
{
	check(Socket);
	check(Socket->IsConnected());
	Socket->Send(message);
}

void UWeb3RpcEngineSys::GetProtocolVersion()
{
}


void UWeb3RpcEngineSys::GetBalance(FString& address)
{
	FReqEthGetBalance req = FReqEthGetBalance();
	req.init(address);
	CallRpc<FReqEthGetBalance>(req);
}

void UWeb3RpcEngineSys::InitContract(FString abiUrl, FString address)
{
	FWsInitContract data;
	data.abi_url = abiUrl;
	data.address = address;
	WsCall<FWsInitContract>(wsfunc_init_contract, data);
}

void UWeb3RpcEngineSys::OnInitContractCallback(FString funcName, FString data, FString message)
{
	if (funcName != wsfunc_init_contract) {
		return;
	}
	if (message != status_success) {
		UE_LOG(Web3RPC, Error, TEXT("init contract error: %s"), *message);
		return;
	}
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(data);
	TSharedPtr<FJsonObject> jsonObject;
	FJsonSerializer::Deserialize(Reader, jsonObject);
	if (!jsonObject.IsValid()) {
		UE_LOG(Web3RPC, Error, TEXT("res json deserialize error: %s"), *data);
		return;
	}
	FString address = jsonObject->GetStringField(TEXT("address"));
	if (!_contractArray.Contains(address)) {
		_contractArray.Add(address);
	}
	if (contractInitSuccess.IsBound()) {
		contractInitSuccess.Broadcast(address);
	}
}

