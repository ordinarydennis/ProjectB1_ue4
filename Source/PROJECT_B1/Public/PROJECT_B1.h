// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//최적화 할 때 수정 하기
//#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "B1Resources.h"
#include "DrawDebugHelpers.h"

DECLARE_LOG_CATEGORY_EXTERN(B1, Log, All);
#define B1LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define B1LOG_S(Verbosity) UE_LOG(B1, Verbosity, TEXT("%s"), *B1LOG_CALLINFO)
#define B1LOG(Verbosity, Format, ...) UE_LOG(B1, Verbosity, TEXT("%s%s"), *B1LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define B1CHECK(Expr, ...) {if(!(Expr)) { B1LOG(Error, TEXT("ASSERTION: %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}


//typedef int32 ANIMNUM;

UENUM()
enum class ERES_ANIM_NUM
{
	NONE,
	_1000 = 1000,
	_1001,
	_1002,
	_1003,
	_1004,
	_1005,
};

UENUM()
enum class ERES_STATE_MONSTER
{
	IDLE,
	RUN,
	ATTACK,
};

const int NUM_OF_INGAME_SKILL_BTN = 4;
