#include "Breathing.h"

#include "Oxygen.h"

void UBreathingComponent::Breath(const float InDeltaTime, UOxygenComponent* InOxygenComponent)
{
	const bool IsOxygenComponentValid = IsValid(InOxygenComponent);
	
	ElapsedTime += InDeltaTime;
	
	if (BreathingIntervalMode == EBreathingIntervalMode::Continuous && IsOxygenComponentValid)
	{
		InOxygenComponent->ChangeBy(ComputeConsumesValue(InOxygenComponent) / InDeltaTime);
		return;
	}

	if (ElapsedTime < Interval)
	{
		return;
	}

	ElapsedTime = Interval > 0.f ? ElapsedTime - Interval : 0.f;

	if (BreathingIntervalMode == EBreathingIntervalMode::Discrete && IsOxygenComponentValid)
	{
		InOxygenComponent->ChangeBy(ComputeConsumesValue(InOxygenComponent));
	}
}

void UBreathingComponent::ResetTime()
{
	ElapsedTime = 0.f;
}

float UBreathingComponent::GetTime() const
{
	return ElapsedTime;
}

void UBreathingComponent::SetInterval(const float InInterval)
{
	Interval = InInterval;
}

float UBreathingComponent::GetInterval() const
{
	return Interval;
}

float UBreathingComponent::ComputeConsumesValue(const UOxygenComponent* InOxygenComponent) const
{
	const bool IsOxygenComponentValid = IsValid(InOxygenComponent);

	if (BreathingConsumeMode == EBreathingConsumeMode::Absolute)
	{
		return -Consumes;
	}

	if (BreathingConsumeMode == EBreathingConsumeMode::PercentFromCapacity && IsOxygenComponentValid)
	{
		return -Consumes * (100.f / InOxygenComponent->GetCapacity());
	}

	if (BreathingConsumeMode == EBreathingConsumeMode::PercentFromRemains && IsOxygenComponentValid)
	{
		return -Consumes * (100.f / InOxygenComponent->GetRemains());
	}

	return 0.f;
}