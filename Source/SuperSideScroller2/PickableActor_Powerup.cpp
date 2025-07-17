// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Powerup.h"
#include "SuperSideScroller2_Player.h"

void APickableActor_Powerup::BeginPlay() {
	Super::BeginPlay();
}
void APickableActor_Powerup::PlayerPickedUp(class ASuperSideScroller2_Player* Player) {
	Super::PlayerPickedUp(Player);

	Player->IncreaseMovementPowerup();
}