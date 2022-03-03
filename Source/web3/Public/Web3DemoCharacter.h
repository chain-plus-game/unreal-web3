// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <web3/Static/TypeStructure.h>
#include <web3/Public/RpcEngineSys.h>
#include "Web3DemoCharacter.generated.h"

UCLASS()
class WEB3_API AWeb3DemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWeb3DemoCharacter();

	UPROPERTY()
		URpcEngineSys* EthRpc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnRpcCallBack(FString funcName, FString res);

	UFUNCTION()
		void OnContractInitSuccess(FString contractNames);
};
