// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3DemoCharacter.h"
#include "Containers/UnrealString.h"
#include <web3/Public/keccak.h>

// Sets default values
AWeb3DemoCharacter::AWeb3DemoCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeb3DemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	EthRpc = GEngine->GetEngineSubsystem<URpcEngineSys>();
	FString abiUrl = TEXT("https://raw.githubusercontent.com/chain-plus-game/MiracleWarGame/master/src/abstract/MiracleCard.json");
	EthRpc->contractInitSuccess.AddDynamic(this, &AWeb3DemoCharacter::OnContractInitSuccess);
	EthRpc->InitContract(TEXT("CardNFT"), abiUrl);
	/*rpc->rpcCallBack.AddDynamic(this, &AWeb3DemoCharacter::OnRpcCallBack);
	FString address = TEXT("0xe5e0Bd2EdBa9a9AD09CBA7081c31272953Eb8948");
	rpc->GetBalance(address);
	Keccak keccak(Keccak::Keccak256);
	FString funcName = TEXT("baz(uint32,bool)");
	keccak.add(TCHAR_TO_UTF8(*funcName), 16);

	FString myHash3(keccak.getHash().c_str());
	UE_LOG(LogTemp, Warning, TEXT("keccak hash is %s"), *myHash3);*/
}

// Called every frame
void AWeb3DemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWeb3DemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWeb3DemoCharacter::OnRpcCallBack(FString funcName, FString res)
{
	UE_LOG(LogTemp, Warning, TEXT("get rpc call back func:%s"), *funcName);
	FResEthGetBalance data;
	FJsonObjectConverter::JsonObjectStringToUStruct(res, &data, 0, 0);
	FString result = data.result;
	UE_LOG(LogTemp, Warning, TEXT("get rpc call back result:%s"), *result);
}

void AWeb3DemoCharacter::OnContractInitSuccess(FString contractNames)
{
	FString toFunc = TEXT("");
	EthRpc->CallContractFunc(toFunc,);
}

