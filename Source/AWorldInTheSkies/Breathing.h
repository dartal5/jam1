#pragma once

#include "Breathing.generated.h"

class UOxygenComponent;

UENUM()
enum class EBreathingConsumeMode
{
	InAbsolute,
	InPercentFromRemains,
	InPercentFromCapacity
};

UENUM()
enum class EBreathingIntervalMode
{
	Discrete,
	Continuous
};

UCLASS()
class AWORLDINTHESKIES_API UBreathingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void Breath(const float InDeltaTime, UOxygenComponent& InOxygenComponent);

	UPROPERTY(EditAnywhere)
	float Interval = 1.f;

	UPROPERTY(EditAnywhere)
	float Consumes = 10.f;

	UPROPERTY(EditAnywhere)
	EBreathingConsumeMode BreathingConsumeMode = EBreathingConsumeMode::InAbsolute;

	UPROPERTY(EditAnywhere)
	EBreathingIntervalMode BreathingIntervalMode = EBreathingIntervalMode::Discrete;

	float ComputeConsumesValue(const UOxygenComponent& InOxygenComponent) const;

private:
	float ElapsedTime = 0.f;

};