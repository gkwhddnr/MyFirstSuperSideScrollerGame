// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller2_Player.h"
#include "PlayerProjectile.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"


ASuperSideScroller2_Player::ASuperSideScroller2_Player() {
	// 전력 질주 기본값 설정
	bIsSprinting = false;

	// Max Walk Speed 값 설정
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ASuperSideScroller2_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// 항상 필요하진 않으나 부모 클래스 함수 호출하는 것이 좋음.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Sprint 함수 호출하도록 바인딩
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASuperSideScroller2_Player::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASuperSideScroller2_Player::StopSprinting);
	PlayerInputComponent->BindAction("ThrowProjectile", IE_Pressed, this, &ASuperSideScroller2_Player::ThrowProjectile);
}

void ASuperSideScroller2_Player::Sprint() {
	if (!bIsSprinting) {
		bIsSprinting = true;
		if (bHasPowerupActive) {
			GetCharacterMovement()->MaxWalkSpeed = 900.f;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 500.f;
		}
	}
}	
void ASuperSideScroller2_Player::StopSprinting() {
	if (bIsSprinting) {
		bIsSprinting = false;
		if (bHasPowerupActive) {
			GetCharacterMovement()->MaxWalkSpeed = 500.f;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 300.f;
		}
	}
}

void ASuperSideScroller2_Player::ThrowProjectile() {
	if (ThrowMontage) {
		bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying) {
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 2.f);
		}
	}

}

void ASuperSideScroller2_Player::SpawnProjectile() {
	if (PlayerProjectile) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			FRotator Rotation = GetActorForwardVector().Rotation();

			APlayerProjectile* Projectile = world->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
			if (Projectile) {
				Projectile->CollisionComp->MoveIgnoreActors.Add(SpawnParams.Owner);
			}
		}
	}
}

void ASuperSideScroller2_Player::IncrementNumberofCollectables(int32 Value) {
	// 전달된 정수 값이 0보다 작거나 같은 경우 NumberofCollectables 변수 증가 x
	if (Value <= 0) {
		return;	// 함수 종료
	}
	else {
		NumberofCollectables += Value;
		UE_LOG(LogTemp, Warning, TEXT("Number of Coins : %d"), NumberofCollectables);
	}
}

void ASuperSideScroller2_Player::IncreaseMovementPowerup() {
	bHasPowerupActive = true;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->JumpZVelocity = 1500.f;

	UWorld* World = GetWorld();
	if (World) {
		// 8초 동안 효력 발생
		World->GetTimerManager().SetTimer(PowerupHandle, this, &ASuperSideScroller2_Player::EndPowerup, 8.f, false);
	}
}
// 파워 업 효과를 활성화하기 위해 파워 업 물약 클래스에서 호출할 함수


void ASuperSideScroller2_Player::EndPowerup() {
	bHasPowerupActive = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;

	UWorld* World = GetWorld();
	if (World) {
		// 타이머가 유효하지 않고, 플레이어에게 영향을 미치지 않도록 설정
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}