#pragma once

#include "Breathing.generated.h"

class UOxygenComponent;

UENUM(BlueprintType)
enum class EBreathingConsumeMode : uint8
{
	Absolute,
	PercentFromRemains,
	PercentFromCapacity
};

UENUM(BlueprintType)
enum class EBreathingIntervalMode : uint8
{
	Discrete,
	Continuous
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API UBreathingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Breath(const float InDeltaTime, UOxygenComponent* InOxygenComponent);
	
	UFUNCTION(BlueprintCallable)
	void ResetTime();

	UFUNCTION(BlueprintCallable)
	float GetTime() const;

	UFUNCTION(BlueprintCallable)
	void SetInterval(const float InInterval);
	
	UFUNCTION(BlueprintCallable)
	float GetInterval() const;

	UPROPERTY(EditAnywhere)
	float Consumes = 10.f;

	UPROPERTY(EditAnywhere)
	EBreathingConsumeMode BreathingConsumeMode = EBreathingConsumeMode::Absolute;

	UPROPERTY(EditAnywhere)
	EBreathingIntervalMode BreathingIntervalMode = EBreathingIntervalMode::Discrete;

	UFUNCTION(BlueprintCallable)
	float ComputeConsumesValue(const UOxygenComponent* InOxygenComponent) const;

protected:
	UPROPERTY(EditAnywhere)
	float Interval = 1.f;

private:
	float ElapsedTime = 0.f;

};