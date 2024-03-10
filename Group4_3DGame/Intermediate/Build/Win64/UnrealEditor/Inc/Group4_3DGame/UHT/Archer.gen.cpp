// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Group4_3DGame/Public/Archer.h"
#include "InputActionValue.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArcher() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	ENHANCEDINPUT_API UScriptStruct* Z_Construct_UScriptStruct_FInputActionValue();
	GROUP4_3DGAME_API UClass* Z_Construct_UClass_AArcher();
	GROUP4_3DGAME_API UClass* Z_Construct_UClass_AArcher_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Group4_3DGame();
// End Cross Module References
	DEFINE_FUNCTION(AArcher::execLookAround)
	{
		P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LookAround(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AArcher::execMove)
	{
		P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Move(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	void AArcher::StaticRegisterNativesAArcher()
	{
		UClass* Class = AArcher::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LookAround", &AArcher::execLookAround },
			{ "Move", &AArcher::execMove },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AArcher_LookAround_Statics
	{
		struct Archer_eventLookAround_Parms
		{
			FInputActionValue Value;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AArcher_LookAround_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AArcher_LookAround_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Archer_eventLookAround_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_LookAround_Statics::NewProp_Value_MetaData), Z_Construct_UFunction_AArcher_LookAround_Statics::NewProp_Value_MetaData) }; // 1693336646
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AArcher_LookAround_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AArcher_LookAround_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AArcher_LookAround_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AArcher_LookAround_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AArcher, nullptr, "LookAround", nullptr, nullptr, Z_Construct_UFunction_AArcher_LookAround_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_LookAround_Statics::PropPointers), sizeof(Z_Construct_UFunction_AArcher_LookAround_Statics::Archer_eventLookAround_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_LookAround_Statics::Function_MetaDataParams), Z_Construct_UFunction_AArcher_LookAround_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_LookAround_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AArcher_LookAround_Statics::Archer_eventLookAround_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AArcher_LookAround()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AArcher_LookAround_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AArcher_Move_Statics
	{
		struct Archer_eventMove_Parms
		{
			FInputActionValue Value;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AArcher_Move_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AArcher_Move_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Archer_eventMove_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_Move_Statics::NewProp_Value_MetaData), Z_Construct_UFunction_AArcher_Move_Statics::NewProp_Value_MetaData) }; // 1693336646
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AArcher_Move_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AArcher_Move_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AArcher_Move_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AArcher_Move_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AArcher, nullptr, "Move", nullptr, nullptr, Z_Construct_UFunction_AArcher_Move_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_Move_Statics::PropPointers), sizeof(Z_Construct_UFunction_AArcher_Move_Statics::Archer_eventMove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_Move_Statics::Function_MetaDataParams), Z_Construct_UFunction_AArcher_Move_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AArcher_Move_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AArcher_Move_Statics::Archer_eventMove_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AArcher_Move()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AArcher_Move_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AArcher);
	UClass* Z_Construct_UClass_AArcher_NoRegister()
	{
		return AArcher::StaticClass();
	}
	struct Z_Construct_UClass_AArcher_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ArcherCameraComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ArcherCameraComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ArcherMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ArcherMesh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IMC_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IMC;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AArcher_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Group4_3DGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AArcher_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AArcher_LookAround, "LookAround" }, // 2366894246
		{ &Z_Construct_UFunction_AArcher_Move, "Move" }, // 1084863929
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Archer.h" },
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_ArcherCameraComponent_MetaData[] = {
		{ "Category", "Archer" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n\x09 * Components\n\x09 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Archer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* Components" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_ArcherCameraComponent = { "ArcherCameraComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, ArcherCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_ArcherCameraComponent_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_ArcherCameraComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_ArcherMesh_MetaData[] = {
		{ "Category", "Archer" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_ArcherMesh = { "ArcherMesh", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, ArcherMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_ArcherMesh_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_ArcherMesh_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_IMC_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n\x09 * Input Mapping Context and Actions\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Archer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* Input Mapping Context and Actions" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_IMC = { "IMC", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, IMC), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_IMC_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_IMC_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_MoveAction_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_MoveAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_JumpAction_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_JumpAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AArcher_Statics::NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Archer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AArcher_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AArcher, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::NewProp_LookAction_MetaData), Z_Construct_UClass_AArcher_Statics::NewProp_LookAction_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AArcher_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_ArcherCameraComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_ArcherMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_IMC,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_MoveAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_JumpAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AArcher_Statics::NewProp_LookAction,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AArcher_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AArcher>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AArcher_Statics::ClassParams = {
		&AArcher::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AArcher_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::Class_MetaDataParams), Z_Construct_UClass_AArcher_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AArcher_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AArcher()
	{
		if (!Z_Registration_Info_UClass_AArcher.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AArcher.OuterSingleton, Z_Construct_UClass_AArcher_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AArcher.OuterSingleton;
	}
	template<> GROUP4_3DGAME_API UClass* StaticClass<AArcher>()
	{
		return AArcher::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AArcher);
	AArcher::~AArcher() {}
	struct Z_CompiledInDeferFile_FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AArcher, AArcher::StaticClass, TEXT("AArcher"), &Z_Registration_Info_UClass_AArcher, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AArcher), 1841140027U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_1056149017(TEXT("/Script/Group4_3DGame"),
		Z_CompiledInDeferFile_FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
