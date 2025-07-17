// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"
#include "SuperSideScroller2_Player.h"
#include "Components/SkeletalMeshComponent.h"

void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	ASuperSideScroller2_Player* Player = Cast<ASuperSideScroller2_Player>(MeshComp->GetOwner());
	if (Player) {
		Player->SpawnProjectile();
	}
}