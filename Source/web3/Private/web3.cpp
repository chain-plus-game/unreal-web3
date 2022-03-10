// Copyright Epic Games, Inc. All Rights Reserved.

#include "web3.h"
#include "ISettingsModule.h"
#include <web3/Public/Web3RpcEngineSys.h>
#define LOCTEXT_NAMESPACE "Fweb3Module"

void Fweb3Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingModule->RegisterSettings("Project", "Plugins", "Web3",
			LOCTEXT("RuntimeSettingsName", "Web3"),
			LOCTEXT("RuntimeSettingsDescription", "Configure web3"),
			GetMutableDefault<UWeb3RpcEngineSys>()
		);
	}
}

void Fweb3Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Web3");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fweb3Module, web3)