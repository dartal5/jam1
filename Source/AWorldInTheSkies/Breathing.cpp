#include "Breathing.h"

#include "Oxygen.h"

void UBreathingComponent::Breath(const float InDeltaTime, UOxygenComponent& InOxygenComponent)
{
	ElapsedTime += InDeltaTime;

	if (BreathingIntervalMode == EBreathingIntervalMode::Continuous)
	{
		InOxygenComponent.ChangeBy(ComputeConsumesValue(InOxygenComponent) / InDeltaTime);
		return;
	}

	if (ElapsedTime < Interval)
	{
		return;
	}

	ElapsedTime = Interval > 0.f ? ElapsedTime - Interval : 0.f;

	if (BreathingIntervalMode == EBreathingIntervalMode::Discrete)
	{
		InOxygenComponent.ChangeBy(ComputeConsumesValue(InOxygenComponent));
	}
}

float UBreathingComponent::ComputeConsumesValue(const UOxygenComponent& InOxygenComponent) const
{
	if (BreathingConsumeMode == EBreathingConsumeMode::InAbsolute)
	{
		return -Consumes;
	}

	if (BreathingConsumeMode == EBreathingConsumeMode::InPercentFromCapacity)
	{
		return -Consumes * (100.f / InOxygenComponent.GetCapacity());
	}

	if (BreathingConsumeMode == EBreathingConsumeMode::InPercentFromRemains)
	{
		return -Consumes * (100.f / InOxygenComponent.GetRemains());
	}

	return 0.f;
}