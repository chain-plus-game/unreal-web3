// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "RpcEngineSys.generated.h"

/**
 * 
 */
UCLASS(Config = Engine)
class WEB3_API URpcEngineSys : public UEngineSubsystem
{
	GENERATED_BODY()
	
	UPROPERTY(Config)
		FString ETHRpcUrl;

public:

	UFUNCTION(BlueprintCallable, Category = "Web3")
		void GetProtocolVersion();
};
