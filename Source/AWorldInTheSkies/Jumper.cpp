#include "Jumper.h"

#include "Oxygen.h"

AJumper::AJumper(const FObjectInitializer& InObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	OxygenComponent = CreateDefaultSubobject<UOxygenComponent>(TEXT("OxygenComponent"));
	AddOwnedComponent(OxygenComponent);
}

void AJumper::BeginPlay()
{
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
}

void AJumper::HandleOxygenRemainsChange(const int32 OldValue, const int32 NewValue)
{
	if (NewValue == 0)
	{
		// DIE
	}
}