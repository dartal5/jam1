#include "Oxygen.h"

void UOxygenComponent::Initialize(const float InCapacity, const float InRemains)
{
	Capacity = FMath::Max(InCapacity, 0.f);
	Remains = FMath::Min(Capacity, FMath::Max(InRemains, 0.f));
}

void UOxygenComponent::Reset()
{
	Remains = Capacity;
}

void UOxygenComponent::Set(const float InRemains)
{
	Remains = FMath::Min(Capacity, FMath::Max(InRemains, 0.f));
}

float UOxygenComponent::GetRemains() const
{
	return Remains;
}

float UOxygenComponent::GetCapacity() const
{
	return Capacity;
}

void UOxygenComponent::ChangeBy(const float InValue)
{
	const float OldValue = Remains;
	Remains = FMath::Min(Capacity, FMath::Max(Remains + InValue, 0.f));
	OnRemainsChange.Broadcast(OldValue, Remains);
}