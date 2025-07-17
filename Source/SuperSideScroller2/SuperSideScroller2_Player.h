// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScroller2Character.h"
#include "SuperSideScroller2_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER2_API ASuperSideScroller2_Player : public ASuperSideScroller2Character
{
	GENERATED_BODY()

public:
	ASuperSideScroller2_Player();

	void Sprint();	// ���� ����
	void StopSprinting();	// ���� ���� ����
	void ThrowProjectile();
	void SpawnProjectile();
	void IncrementNumberofCollectables(int32 Value);	// �÷��̾ ������ ������ ���� �����ϴµ� ����� ���� �Լ�
	void IncreaseMovementPowerup();	// �Ŀ� �� ȿ���� Ȱ��ȭ�ϱ� ���� �Ŀ� �� ���� Ŭ�������� ȣ���� �Լ�

protected:
	// �÷��̾� �Է� ������Ʈ ������ ���� �θ� ĳ���� Ŭ���� �Լ� ������
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UFUNCTION(BlueprintPure)	// UMG�� ����� �� �ֵ��� �������Ʈ�� �����Ŵ.
	int32 GetCurrentNumberofCollectables() { return NumberofCollectables; }

private:
	void EndPowerup();

private:
	// ���� ���� ������ Ȯ���ϴ� ����, ������ġ
	bool bIsSprinting;

	bool bHasPowerupActive;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerProjectile> PlayerProjectile;

	int32 NumberofCollectables;	// �÷��̾ ������ ������ �� ���� (�� ���� ���ϵ��� private�� ����)

	FTimerHandle PowerupHandle;	// Ÿ�̸� �����ǰ� ����� �ð� ����
};
