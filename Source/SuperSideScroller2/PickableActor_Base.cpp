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
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");	// �÷��̾� ĳ���Ϳ��� ������ �ʿ�
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
	RootComponent = CollisionComp;	// USphereComponent�� �� ������ ��Ʈ ������Ʈ�� ����
	

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// MeshComp�� ��Ʈ ������Ʈ CollisionComp�� ����
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	// �⺻������ �浹�� �߻��ϸ� �ȵ�.
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