// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WaveRunner/WaveRunnerGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWaveRunnerGameMode() {}
// Cross Module References
	WAVERUNNER_API UClass* Z_Construct_UClass_AWaveRunnerGameMode_NoRegister();
	WAVERUNNER_API UClass* Z_Construct_UClass_AWaveRunnerGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_WaveRunner();
// End Cross Module References
	void AWaveRunnerGameMode::StaticRegisterNativesAWaveRunnerGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWaveRunnerGameMode);
	UClass* Z_Construct_UClass_AWaveRunnerGameMode_NoRegister()
	{
		return AWaveRunnerGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AWaveRunnerGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWaveRunnerGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_WaveRunner,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWaveRunnerGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * The GameMode defines the game being played. It governs the game rules, scoring, what actors\n * are allowed to exist in this game type, and who may enter the game.\n *\n * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of WaveRunnerCharacter\n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "WaveRunnerGameMode.h" },
		{ "ModuleRelativePath", "WaveRunnerGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "The GameMode defines the game being played. It governs the game rules, scoring, what actors\nare allowed to exist in this game type, and who may enter the game.\n\nThis game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of WaveRunnerCharacter" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWaveRunnerGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWaveRunnerGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWaveRunnerGameMode_Statics::ClassParams = {
		&AWaveRunnerGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AWaveRunnerGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AWaveRunnerGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AWaveRunnerGameMode()
	{
		if (!Z_Registration_Info_UClass_AWaveRunnerGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWaveRunnerGameMode.OuterSingleton, Z_Construct_UClass_AWaveRunnerGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWaveRunnerGameMode.OuterSingleton;
	}
	template<> WAVERUNNER_API UClass* StaticClass<AWaveRunnerGameMode>()
	{
		return AWaveRunnerGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWaveRunnerGameMode);
	struct Z_CompiledInDeferFile_FID_WaveRunner_Source_WaveRunner_WaveRunnerGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_WaveRunner_Source_WaveRunner_WaveRunnerGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWaveRunnerGameMode, AWaveRunnerGameMode::StaticClass, TEXT("AWaveRunnerGameMode"), &Z_Registration_Info_UClass_AWaveRunnerGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWaveRunnerGameMode), 2710683780U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_WaveRunner_Source_WaveRunner_WaveRunnerGameMode_h_400644841(TEXT("/Script/WaveRunner"),
		Z_CompiledInDeferFile_FID_WaveRunner_Source_WaveRunner_WaveRunnerGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_WaveRunner_Source_WaveRunner_WaveRunnerGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
