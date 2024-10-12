// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RETURN_XENIA/RETURN_XENIAGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRETURN_XENIAGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	RETURN_XENIA_API UClass* Z_Construct_UClass_ARETURN_XENIAGameMode();
	RETURN_XENIA_API UClass* Z_Construct_UClass_ARETURN_XENIAGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_RETURN_XENIA();
// End Cross Module References
	void ARETURN_XENIAGameMode::StaticRegisterNativesARETURN_XENIAGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARETURN_XENIAGameMode);
	UClass* Z_Construct_UClass_ARETURN_XENIAGameMode_NoRegister()
	{
		return ARETURN_XENIAGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ARETURN_XENIAGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_RETURN_XENIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "RETURN_XENIAGameMode.h" },
		{ "ModuleRelativePath", "RETURN_XENIAGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARETURN_XENIAGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::ClassParams = {
		&ARETURN_XENIAGameMode::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ARETURN_XENIAGameMode()
	{
		if (!Z_Registration_Info_UClass_ARETURN_XENIAGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARETURN_XENIAGameMode.OuterSingleton, Z_Construct_UClass_ARETURN_XENIAGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARETURN_XENIAGameMode.OuterSingleton;
	}
	template<> RETURN_XENIA_API UClass* StaticClass<ARETURN_XENIAGameMode>()
	{
		return ARETURN_XENIAGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARETURN_XENIAGameMode);
	ARETURN_XENIAGameMode::~ARETURN_XENIAGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_User_Documents_Unreal_Projects_RETURN_XENIA_RETURN_XENIA_Source_RETURN_XENIA_RETURN_XENIAGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_User_Documents_Unreal_Projects_RETURN_XENIA_RETURN_XENIA_Source_RETURN_XENIA_RETURN_XENIAGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARETURN_XENIAGameMode, ARETURN_XENIAGameMode::StaticClass, TEXT("ARETURN_XENIAGameMode"), &Z_Registration_Info_UClass_ARETURN_XENIAGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARETURN_XENIAGameMode), 1785083212U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_User_Documents_Unreal_Projects_RETURN_XENIA_RETURN_XENIA_Source_RETURN_XENIA_RETURN_XENIAGameMode_h_2046698168(TEXT("/Script/RETURN_XENIA"),
		Z_CompiledInDeferFile_FID_Users_User_Documents_Unreal_Projects_RETURN_XENIA_RETURN_XENIA_Source_RETURN_XENIA_RETURN_XENIAGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_User_Documents_Unreal_Projects_RETURN_XENIA_RETURN_XENIA_Source_RETURN_XENIA_RETURN_XENIAGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
