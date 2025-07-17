// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller2_Brick.h"
#include "SuperSideScroller2_Player.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASuperSideScroller2_Brick::ASuperSideScroller2_Brick()
{
	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	BrickMesh->SetCollisionProfileName("BlockAll");		// �÷��̾ ��� �÷��� �̵��ϴ� �������� ��� (�浹 �⺻ �߻�)
	RootComponent = BrickMesh;

	BrickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BrickCollision"));
	BrickCollision->SetCollisionProfileName("BlockAll");
	BrickCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	BrickCollision->OnComponentHit.AddDynamic(this, &ASuperSideScroller2_Brick::OnHit);

}

// Called when the game starts or when spawned
void ASuperSideScroller2_Brick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASuperSideScroller2_Brick::AddCollectable(class ASuperSideScroller2_Player* Player) {
	Player->IncrementNumberofCollectables(CollectableValue);
}	// IncreaseNumberofCollectables() �Լ� ȣ���ϵ��� ���� ����

void ASuperSideScroller2_Brick::PlayHitSound() {
	UWorld* World = GetWorld();
	if (World) {
		if (HitSound) {
			UGameplayStatics::SpawnSoundAtLocation(World, HitSound, GetActorLocation());
		}
	}
}	// ���� ���

void ASuperSideScroller2_Brick::PlayHitExplosion() {
	UWorld* World = GetWorld();
	if (World) {
		if (Explosion) {
			UGameplayStatics::SpawnEmitterAtLocation(World, Explosion, GetActorTransform());
		}
	}
}	// ��ƼŬ ����Ʈ ���


void ASuperSideScroller2_Brick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	ASuperSideScroller2_Player* Player = Cast<ASuperSideScroller2_Player>(OtherActor);
	
	if (Player && bHasCollectable) {	// bHasCollectable Ȱ��ȭ�Ǿ� �ִٸ�
		AddCollectable(Player);	//  Collectable ���� (coin �� ����)
		PlayHitSound();
		PlayHitExplosion();
		Destroy();
	}
}