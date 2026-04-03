// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/CapsuleComponent.h"
#include "BaseProjectile.h"

#include "BasePawn.generated.h"

UCLASS()
class BATTLEBLASTER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BaseMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TurretMeshComponent;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DestructionParticles;
	
	UPROPERTY(EditAnywhere)
	USoundBase* DestructionSound;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DestructionCameraShakeClass;
	
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	void HandleDestruction();
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.0f;

};
