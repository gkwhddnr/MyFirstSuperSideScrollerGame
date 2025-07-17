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
	// ���� ���� �⺻�� ����
	bIsSprinting = false;

	// Max Walk Speed �� ����
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ASuperSideScroller2_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// �׻� �ʿ����� ������ �θ� Ŭ���� �Լ� ȣ���ϴ� ���� ����.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Sprint �Լ� ȣ���ϵ��� ���ε�
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
	// ���޵� ���� ���� 0���� �۰ų� ���� ��� NumberofCollectables ���� ���� x
	if (Value <= 0) {
		return;	// �Լ� ����
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
		// 8�� ���� ȿ�� �߻�
		World->GetTimerManager().SetTimer(PowerupHandle, this, &ASuperSideScroller2_Player::EndPowerup, 8.f, false);
	}
}
// �Ŀ� �� ȿ���� Ȱ��ȭ�ϱ� ���� �Ŀ� �� ���� Ŭ�������� ȣ���� �Լ�


void ASuperSideScroller2_Player::EndPowerup() {
	bHasPowerupActive = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;

	UWorld* World = GetWorld();
	if (World) {
		// Ÿ�̸Ӱ� ��ȿ���� �ʰ�, �÷��̾�� ������ ��ġ�� �ʵ��� ����
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}