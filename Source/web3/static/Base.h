// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include "Base.generated.h"

USTRUCT()
struct FOutMsg {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		int MsgType;

	UPROPERTY()
		FString MsgInfo;
};

// 消息基类
USTRUCT(BlueprintType)
struct FMsgBase{

	GENERATED_USTRUCT_BODY()
public:

	int MsgType;

	FString MsgInfo;

	FMsgBase() {};

	virtual ~FMsgBase() {};

	template<typename T>
	void decode(FString& outStr) {
		FOutMsg out = FOutMsg(); // 需要填充有效信息
		out.MsgType = MsgType;
		FString info;
		FJsonObjectConverter::UStructToJsonObjectString(T::StaticStruct(), this, info, 0, 0);
		out.MsgInfo = info;
		FJsonObjectConverter::UStructToJsonObjectString(FOutMsg::StaticStruct(), &out, outStr, 0, 0);
	}
	
	void GenStr(FString& outStr) {

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		JsonObject->SetStringField(TEXT("MsgInfo"), MsgInfo);
		JsonObject->SetNumberField(TEXT("MsgType"), MsgType);

		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&outStr);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	}

	static FMsgBase encode(const FString& inStr){

		auto msgStruct = FMsgBase();

		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(inStr);

		TSharedPtr<FJsonObject> rRoot;

		bool bSuccessful = FJsonSerializer::Deserialize(Reader, rRoot);

		if (bSuccessful) {
			if (rRoot->HasField(TEXT("MsgType"))) {
				msgStruct.MsgType = rRoot->GetNumberField(TEXT("MsgType"));
			}
			if (rRoot->HasField(TEXT("MsgInfo"))) {
				msgStruct.MsgInfo = rRoot->GetStringField(TEXT("MsgInfo"));
			}
		}
		return msgStruct;
	} 

	template<typename T>
	void GetMsg(T* OutStruct) {
		FJsonObjectConverter::JsonObjectStringToUStruct<T>(MsgInfo, OutStruct, 0, 0);
	}
};
