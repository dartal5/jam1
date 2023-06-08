#include "Health.h"

void UHealthComponent::Initialize(const float InCapacity, const float InRemains)
{
	Capacity = FMath::Max(InCapacity, 0.f);
	Remains = FMath::Min(Capacity, FMath::Max(InRemains, 0.f));
}

void UHealthComponent::Reset()
{
	Remains = Capacity;
}

void UHealthComponent::Set(const float InRemains)
{
	Remains = FMath::Min(Capacity, FMath::Max(InRemains, 0.f));
}

float UHealthComponent::GetRemains() const
{
	return Remains;
}

float UHealthComponent::GetCapacity() const
{
	return Capacity;
}

void UHealthComponent::ChangeBy(const float InValue)
{
	const float OldValue = Remains;
	Remains = FMath::Min(Capacity, FMath::Max(Remains + InValue, 0.f));
	OnRemainsChange.Broadcast(OldValue, Remains);
}