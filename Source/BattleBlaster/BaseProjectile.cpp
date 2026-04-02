// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "BasePawn.h"
#include "EnemyTower.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	SetRootComponent(BaseMeshComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = BaseMeshComponent;
	
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMeshComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (AActor* MyOwner = GetOwner())
	{
		if (OtherActor && (OtherActor != MyOwner) && (OtherActor != this))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetActorNameOrLabel());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
	
	Destroy();
}

