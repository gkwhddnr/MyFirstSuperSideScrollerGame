// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuperSideScroller2_Brick.generated.h"

UCLASS()
class SUPERSIDESCROLLER2_API ASuperSideScroller2_Brick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuperSideScroller2_Brick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AddCollectable(class ASuperSideScroller2_Player* Player);	// IncreaseNumberofCollectables() 함수 호출하도록 참조 전달
	void PlayHitSound();	// 사운드 재생
	void PlayHitExplosion();	// 파티클 이펙트 재생

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UStaticMeshComponent* BrickMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UBoxComponent* BrickCollision;

	UPROPERTY(EditAnywhere)
	bool bHasCollectable;	// 플레이어가 찾을 수집용 코인을 포함하는지 여부 결정

	UPROPERTY(EditAnywhere)
	int32 CollectableValue = 1;

public:
	// 벽돌 파괴할 때 멋진 효과 보여주기 위한 변수들
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brick)
	class UParticleSystem* Explosion;

};
