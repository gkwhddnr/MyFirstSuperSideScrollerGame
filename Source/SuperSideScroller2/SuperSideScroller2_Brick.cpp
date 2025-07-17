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
	BrickMesh->SetCollisionProfileName("BlockAll");		// 플레이어가 밟고 플랫폼 이동하는 목적으로 사용 (충돌 기본 발생)
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
}	// IncreaseNumberofCollectables() 함수 호출하도록 참조 전달

void ASuperSideScroller2_Brick::PlayHitSound() {
	UWorld* World = GetWorld();
	if (World) {
		if (HitSound) {
			UGameplayStatics::SpawnSoundAtLocation(World, HitSound, GetActorLocation());
		}
	}
}	// 사운드 재생

void ASuperSideScroller2_Brick::PlayHitExplosion() {
	UWorld* World = GetWorld();
	if (World) {
		if (Explosion) {
			UGameplayStatics::SpawnEmitterAtLocation(World, Explosion, GetActorTransform());
		}
	}
}	// 파티클 이펙트 재생


void ASuperSideScroller2_Brick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	ASuperSideScroller2_Player* Player = Cast<ASuperSideScroller2_Player>(OtherActor);
	
	if (Player && bHasCollectable) {	// bHasCollectable 활성화되어 있다면
		AddCollectable(Player);	//  Collectable 가능 (coin 수 증가)
		PlayHitSound();
		PlayHitExplosion();
		Destroy();
	}
}