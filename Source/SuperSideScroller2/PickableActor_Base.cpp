// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"
#include "SuperSideScroller2_Player.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickableActor_Base::APickableActor_Base()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(30.f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");	// 플레이어 캐릭터와의 오버랩 필요
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
	RootComponent = CollisionComp;	// USphereComponent를 이 액터의 루트 컴포넌트로 설정
	

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// MeshComp와 루트 컴포넌트 CollisionComp와 연결
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	// 기본적으로 충돌이 발생하면 안됨.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));
}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Base::PlayerPickedUp(class ASuperSideScroller2_Player* Player) {
	const UWorld* World = GetWorld();

	if (World) {
		if (pickupSound) {
			UGameplayStatics::SpawnSoundAtLocation(World, pickupSound, GetActorLocation());
		}
	}
	
	Destroy();
}


void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult) {
	ASuperSideScroller2_Player* Player = Cast<ASuperSideScroller2_Player>(OtherActor);

	if (Player) {
		PlayerPickedUp(Player);
	}
}