#include "Oxygen.h"

void UOxygenComponent::Initialize(const int32 InCapacity, const int32 InRemains)
{
	Capacity = InCapacity;
	Remains = InRemains;
}

int32 UOxygenComponent::GetRemains() const
{
	return Remains;
}

int32 UOxygenComponent::GetCapacity() const
{
	return Capacity;
}

void UOxygenComponent::Increase(const int32 InValue)
{
	const int32 OldValue = Remains;
	Remains = FMath::Min(Remains + FMath::Max(InValue, 0), Capacity);
	OnRemainsChange.Broadcast(OldValue, Remains);
}

void UOxygenComponent::Decrease(const int32 InValue)
{
	const int32 OldValue = Remains;
	Remains = FMath::Max(Remains - FMath::Max(InValue, 0), 0);
	OnRemainsChange.Broadcast(OldValue, Remains);
}