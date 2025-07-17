// Fill out your copyright notice in the Description page of Project Settings.


#include "PikableActor_Collectable.h"
#include "SuperSideScroller2_Player.h"


void APikableActor_Collectable::BeginPlay() {
	Super::BeginPlay();
}

void APikableActor_Collectable::PlayerPickedUp(ASuperSideScroller2_Player* Player) {
	Player->IncrementNumberofCollectables(CollectableValue);

	Super::PlayerPickedUp(Player);
}