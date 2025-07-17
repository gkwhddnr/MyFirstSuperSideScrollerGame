// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScroller2Character.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER2_API AEnemyBase : public ASuperSideScroller2Character
{
	GENERATED_BODY()
	
public:
	void DestroyEnemy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;
};
