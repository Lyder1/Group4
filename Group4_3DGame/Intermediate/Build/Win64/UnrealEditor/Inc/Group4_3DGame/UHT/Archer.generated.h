// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Archer.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FInputActionValue;
#ifdef GROUP4_3DGAME_Archer_generated_h
#error "Archer.generated.h already included, missing '#pragma once' in Archer.h"
#endif
#define GROUP4_3DGAME_Archer_generated_h

#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_SPARSE_DATA
#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execLookAround); \
	DECLARE_FUNCTION(execMove);


#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_ACCESSORS
#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAArcher(); \
	friend struct Z_Construct_UClass_AArcher_Statics; \
public: \
	DECLARE_CLASS(AArcher, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Group4_3DGame"), NO_API) \
	DECLARE_SERIALIZER(AArcher)


#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AArcher(AArcher&&); \
	NO_API AArcher(const AArcher&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AArcher); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AArcher); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AArcher) \
	NO_API virtual ~AArcher();


#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_15_PROLOG
#define FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_SPARSE_DATA \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_ACCESSORS \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_INCLASS_NO_PURE_DECLS \
	FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GROUP4_3DGAME_API UClass* StaticClass<class AArcher>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Group4_3DGame_Source_Group4_3DGame_Public_Archer_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
