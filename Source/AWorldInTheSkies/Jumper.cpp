#include "Jumper.h"

#include "Oxygen.h"
#include "Breathing.h"

AJumper::AJumper(const FObjectInitializer& InObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

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
		BreathingComponent->Breath(InDeltaTime, *OxygenComponent);
	}
}

void AJumper::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(OxygenComponent))
	{
		OxygenComponent->OnRemainsChange.AddUObject(this, &AJumper::HandleOxygenRemainsChange);
	}
}

void AJumper::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(OxygenComponent))
	{
		OxygenComponent->OnRemainsChange.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
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