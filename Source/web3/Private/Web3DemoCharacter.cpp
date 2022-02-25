// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3DemoCharacter.h"
#include <web3/Public/RpcEngineSys.h>

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
	URpcEngineSys* rpc = GEngine->GetEngineSubsystem<URpcEngineSys>();
	rpc->rpcCallBack.AddDynamic(this, &AWeb3DemoCharacter::OnRpcCallBack);
	FString address = TEXT("0xe5e0Bd2EdBa9a9AD09CBA7081c31272953Eb8948");
	rpc->GetBalance(address);
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
}

