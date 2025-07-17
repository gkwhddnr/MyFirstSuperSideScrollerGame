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
	void AddCollectable(class ASuperSideScroller2_Player* Player);	// IncreaseNumberofCollectables() �Լ� ȣ���ϵ��� ���� ����
	void PlayHitSound();	// ���� ���
	void PlayHitExplosion();	// ��ƼŬ ����Ʈ ���

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UStaticMeshComponent* BrickMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UBoxComponent* BrickCollision;

	UPROPERTY(EditAnywhere)
	bool bHasCollectable;	// �÷��̾ ã�� ������ ������ �����ϴ��� ���� ����

	UPROPERTY(EditAnywhere)
	int32 CollectableValue = 1;

public:
	// ���� �ı��� �� ���� ȿ�� �����ֱ� ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brick)
	class UParticleSystem* Explosion;

};
