// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"

// Called when the game starts or when spawned
void ATank::BeginPlay()
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

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComponent"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent);
	
	
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.0f, 16, FColor::Red, false, 0.f);
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
	}
	
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>() ;
	
	UE_LOG(LogTemp, Warning, TEXT("MoveInput called with value: %f"), InputValue);
	
	FVector DeltaForward = FVector(InputValue, 0, 0) * MaxSpeed * GetWorld()->GetDeltaSeconds();
	
	AddActorLocalOffset(DeltaForward, true);
	
	
	
}

void ATank::RotateInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>() ;
	
	UE_LOG(LogTemp, Warning, TEXT("RotateInput called with value: %f"), InputValue);
	
	FRotator DeltaRotate = FRotator(0, InputValue, 0) * TurnSpeed * GetWorld()->GetDeltaSeconds();
	
	AddActorLocalRotation(DeltaRotate, true);
	
}

