// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//최적화 할 때 수정 하기
//#include "CoreMinimal.h"
#include "EngineMinimal.h"
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

const int NUM_OF_INGAME_SKILL_BTN = 4;

#if WITH_EDITOR
#include "EngineGlobals.h"
#include "Engine/Engine.h"

#define print(text)                         if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT(text), false)
#define printc(channel, text)               if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 5.0f, FColor::White, TEXT(text))
#define printf(format, ...)                 if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcf(channel, format, ...)       if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printwarn(text)                     if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT(text), false)
#define printcwarn(channel, text)           if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, TEXT(text))
#define printfwarn(format, ...)             if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcfwarn(channel, format, ...)   if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printerr(text)                      if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT(text), false)
#define printcerr(channel, text)            if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, TEXT(text))
#define printferr(format, ...)              if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcferr(channel, format, ...)    if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printfloat(variable)                if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable), false)
#define printcfloat(channel, variable)      if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable))

#define printvector(variable)               if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()), false)
#define printcvector(channel, variable)     if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))
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


