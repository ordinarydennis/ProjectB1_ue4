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

#if WITH_EDITOR
#include "EngineGlobals.h"
#include "Engine/Engine.h"

//Current Class Name + Function Name where this is called!
#define __CLASS_FUNC__							(FString(__FUNCTION__))
//Current Class where this is called!
#define __CLASS__								(FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )
//Current Function Name where this is called!
#define __FUNC__								(FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))
//Current Line Number in the code where this is called!
//#define _LINE_								(FString::FromInt(__LINE__))
//Current Class and Line Number where this is called!
#define __CLASS_LINE__							(__CLASS__ + "(" + (FString::FromInt(__LINE__)) + ")")
//Current Function Signature where this is called!
#define __FUNC_SIG__								(FString(__FUNCSIG__))

#define print(text)								if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT(text), false)
#define printc(channel, text)					if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 5.0f, FColor::White, TEXT(text))
#define printf(format, ...)						if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcf(channel, format, ...)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printwarn(text)							if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT(text), false)
#define printcwarn(channel, text)				if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, TEXT(text))
#define printfwarn(format, ...)					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcfwarn(channel, format, ...)		if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printerr(text)							if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT(text), false)
#define printcerr(channel, text)				if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, TEXT(text))
#define printferr(format, ...)					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcferr(channel, format, ...)		if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printfloat(variable)					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable), false)
#define printcfloat(channel, variable)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable))

#define printvector(variable)					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()), false)
#define printcvector(channel, variable)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))


#define printcl(Param1)							(GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(__CLASS_LINE__ + ": " + Param1)) )
#define printcl2(Param1,Param2)					(GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(__CLASS_LINE__ + ": " + Param1 + " " + Param2)) )
#define printcl2f(Param1,Param2)				(GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(__CLASS_LINE__ + ": " + Param1 + " " + FString::SanitizeFloat(Param2))) )

//UE LOG!
#define V_LOG(LogCat, Param1)					UE_LOG(LogCat,Warning,TEXT("%s: %s"), *__CLASS_LINE__, *FString(Param1))
#define V_LOG2(LogCat, Param1,Param2)			UE_LOG(LogCat,Warning,TEXT("%s: %s %s"), *__CLASS_LINE__, *FString(Param1),*FString(Param2))
#define V_LOGF(LogCat, Param1,Param2)			UE_LOG(LogCat,Warning,TEXT("%s: %s %f"), *__CLASS_LINE__, *FString(Param1),Param2)
#define V_LOGM(LogCat, FormatString , ...)		UE_LOG(LogCat,Warning,TEXT("%s: %s"), 	*__CLASS_LINE__, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

//refer to https://wiki.unrealengine.com/Logs,_Printing_Class_Name,_Function_Name,_Line_Number_of_your_Calling_Code!

#else
#define print(text)                        
#define printc(channel, text)              
#define printf(format, ...)                 
#define printcf(channel, format, ...)  

#define printwarn(text)                    
#define printcwarn(channel, text)          
#define printfwarn(format, ...)            
#define printcfwarn(channel, format, ...)  

#define printerr(text)                     
#define printcerr(channel, text)           
#define printferr(format, ...)             
#define printcferr(channel, format, ...)   

#define printfloat(variable)               
#define printcfloat(channel, variable)     

#define printvector(variable)              
#define printcvector(channel, variable)    

#endif


