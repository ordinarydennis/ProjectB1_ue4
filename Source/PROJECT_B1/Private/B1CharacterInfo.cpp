// Fill out your copyright notice in the Description page of Project Settings.


#include "B1CharacterInfo.h"

B1CharacterInfo::B1CharacterInfo()
{
}

B1CharacterInfo::~B1CharacterInfo()
{
}
FString B1CharacterInfo::GetResSkMesh()
{
	return ResSkMesh;
}
FString B1CharacterInfo::GetResAnimInst()
{
	return ResAnimInst;
}
FVector2D B1CharacterInfo::GetCapsuleSize()
{
	return CapsuleSize;
}
float B1CharacterInfo::GetMaxHP()
{
	return MaxHP;
}
float B1CharacterInfo::GetDamage()
{
	return Damage;
}
float B1CharacterInfo::GetMaxWalkSpeed()
{
	return MaxWalkSpeed;
}
void B1CharacterInfo::SetResSkMesh(FString resSkMesh)
{
	ResSkMesh = resSkMesh;
}
void B1CharacterInfo::SetResAnimInst(FString resAnimInst)
{
	ResAnimInst = resAnimInst;
}
void B1CharacterInfo::SetCapsuleSize(FVector2D capsuleSize)
{
	CapsuleSize = capsuleSize;
}
void B1CharacterInfo::SetMaxHP(float maxHP)
{
	MaxHP = maxHP;
}
void B1CharacterInfo::SetDamage(float damage)
{
	Damage = damage;
}
void B1CharacterInfo::SetMaxWalkSpeed(float maxWalkSpeed)
{
	MaxWalkSpeed = maxWalkSpeed;
}

