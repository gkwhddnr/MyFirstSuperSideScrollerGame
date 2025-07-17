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

	void Sprint();	// 전력 질주
	void StopSprinting();	// 전력 질주 정지
	void ThrowProjectile();
	void SpawnProjectile();
	void IncrementNumberofCollectables(int32 Value);	// 플레이어가 수집한 동전의 수를 추적하는데 사용할 메인 함수
	void IncreaseMovementPowerup();	// 파워 업 효과를 활성화하기 위해 파워 업 물약 클래스에서 호출할 함수

protected:
	// 플레이어 입력 컴포넌트 설정을 위한 부모 캐릭터 클래스 함수 재정의
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UFUNCTION(BlueprintPure)	// UMG에 사용할 수 있도록 블루프린트에 노출시킴.
	int32 GetCurrentNumberofCollectables() { return NumberofCollectables; }

private:
	void EndPowerup();

private:
	// 전력 질주 중인지 확인하는 변수, 안전장치
	bool bIsSprinting;

	bool bHasPowerupActive;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerProjectile> PlayerProjectile;

	int32 NumberofCollectables;	// 플레이어가 수집한 코인의 수 추적 (값 변경 못하도록 private에 선언)

	FTimerHandle PowerupHandle;	// 타이머 설정되고 경과된 시간 추적
};
