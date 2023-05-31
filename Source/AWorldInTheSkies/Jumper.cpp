#include "Jumper.h"

#include "Oxygen.h"
#include "Breathing.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "GameFramework/PawnMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

AJumper::AJumper(const FObjectInitializer& InObjectInitializer)
{
	OxygenComponent = CreateDefaultSubobject<UOxygenComponent>(TEXT("OxygenComponent"));
	AddOwnedComponent(OxygenComponent);

	BreathingComponent = CreateDefaultSubobject<UBreathingComponent>(TEXT("BreathingComponent"));
	AddOwnedComponent(BreathingComponent);
}

void AJumper::Tick(const float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	if (IsValid(BreathingComponent) && IsValid(OxygenComponent))
	{
		BreathingComponent->Breath(InDeltaTime, OxygenComponent);
	}

	UpdateAnimation();
	UpdateControlRotation();
}

void AJumper::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(OxygenComponent))
	{
		OxygenComponent->OnRemainsChange.AddUObject(this, &AJumper::HandleOxygenRemainsChange);
	}

	AddInputMappingContext();
}

void AJumper::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(OxygenComponent))
	{
		OxygenComponent->OnRemainsChange.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AJumper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
 		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJumper::Move);
	}
}

void AJumper::UpdateAnimation()
{
	if (UPaperFlipbookComponent* sprite = GetSprite())
	{
		sprite->SetFlipbook(PickProperFlipbook());
	}
}

void AJumper::UpdateControlRotation()
{
	AController* controller = GetController();
	if (controller == nullptr || !IsValid(controller))
	{
		return;
	}

	UPawnMovementComponent* movementComponent = GetMovementComponent();
	if (movementComponent ==nullptr)
	{
		return;
	}

	float inputDirection = movementComponent->GetLastInputVector().Y;
	if (inputDirection == 0.0f)
	{
		return;
	}

	controller->SetControlRotation(UKismetMathLibrary::MakeRotator(0.0f, 0.0f, inputDirection > 0.0f ? 90.0f : -90.0f));
}

void AJumper::HandleOxygenRemainsChange(const float OldValue, const float NewValue)
{
	if (NewValue != 0)
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Player Died in Pain... reseting"));

	if (IsValid(OxygenComponent))
	{
		OxygenComponent->Reset();
	}
}

void AJumper::AddInputMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AJumper::Move(const FInputActionValue& Value)
{
	AddMovementInput(FVector{ 0.0f, 1.0f, 0.0f }, Value.Get<float>());
}

UPaperFlipbook* AJumper::PickProperFlipbook()
{
	if (UPawnMovementComponent* movementComponent = GetMovementComponent())
	{
		if (movementComponent->IsFalling())
		{
			return FallingFlipbook;
		}

		if (movementComponent->Velocity.Length() != 0.0f)
		{
			return RunningFlipbook;
		}
	}

	return IdleFlipbook;
}
