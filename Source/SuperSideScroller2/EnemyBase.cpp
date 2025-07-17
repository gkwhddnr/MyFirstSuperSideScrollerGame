// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AEnemyBase::DestroyEnemy() {
	UWorld* World = GetWorld();
	if (World) {
		if (DeathEffect) {
			UGameplayStatics::SpawnEmitterAtLocation(World, DeathEffect, GetActorTransform());
		}
		if (DeathSound) {
			UGameplayStatics::SpawnSoundAtLocation(World, DeathSound, GetActorLocation());
		}
	}
	Destroy();
}