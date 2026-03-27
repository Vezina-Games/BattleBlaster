// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

APlayerTank::APlayerTank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComponent"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent);
	
	
	
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		
		RotateTurret(HitResult.ImpactPoint);
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.0f, 16, FColor::Red, false, 0.f);
	}

}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerTank::MoveInput);
		
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerTank::RotateInput);
		
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerTank::Fire);
		
		UE_LOG(LogTemp, Display, TEXT("Player input component setup"));
	}
	
}

void APlayerTank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>() ;
	
	FVector DeltaForward = FVector(InputValue, 0, 0) * MaxSpeed * GetWorld()->GetDeltaSeconds();
	
	AddActorLocalOffset(DeltaForward, true);
	
	
	
}

void APlayerTank::RotateInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>() ;
	
	FRotator DeltaRotate = FRotator(0, InputValue, 0) * TurnSpeed * GetWorld()->GetDeltaSeconds();
	
	AddActorLocalRotation(DeltaRotate, true);
	
}

