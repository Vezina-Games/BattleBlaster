// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetupAttachment(CapsuleComponent);
	
	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshComponent"));
	TurretMeshComponent->SetupAttachment(BaseMeshComponent);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMeshComponent);
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = (LookAtTarget - GetActorLocation()).GetSafeNormal();
	
	FRotator LookAtRotation = FRotator(0, VectorToTarget.Rotation().Yaw, 0);
	
	FRotator InterpRotation = FMath::RInterpTo(
		TurretMeshComponent->GetComponentRotation(), 
		LookAtRotation, GetWorld()->GetDeltaSeconds(),
		RotationSpeed);
	
	TurretMeshComponent->SetWorldRotation(InterpRotation);
}

void ABasePawn::Fire()
{
	FVector FireLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator FireRotation = ProjectileSpawnPoint->GetComponentRotation();
	
	DrawDebugSphere(GetWorld(), FireLocation, 25.0f, 16, FColor::Red, false, 3.0f);
	
	UE_LOG(LogTemp, Display, TEXT("Firing weapon at"));
}
