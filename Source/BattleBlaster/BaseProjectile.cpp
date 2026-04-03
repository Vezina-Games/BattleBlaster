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
	
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(BaseMeshComponent);
	
	
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMeshComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
	}
	
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
		UE_LOG(LogTemp, Warning, TEXT("Hit %s from %s"), *OtherActor->GetActorNameOrLabel(), *MyOwner->GetActorNameOrLabel());
		
		if (OtherActor && (OtherActor != MyOwner) && (OtherActor != this))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetActorNameOrLabel());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass());
			
			if (HitParticles)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitParticles, Hit.ImpactPoint);
			}
			
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
			}
			if (HitCameraShakeClass)
			{
				if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
				{
					PlayerController->ClientStartCameraShake(HitCameraShakeClass);
				}
			}
		}
	}
	
	Destroy();
}

