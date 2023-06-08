#pragma once

#include "Components/PrimitiveComponent.h"

#include "Health.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void Initialize(const float InCapacity, const float InRemains);

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	void Set(const float InRemains);

	UFUNCTION(BlueprintCallable)
	float GetRemains() const;

	UFUNCTION(BlueprintCallable)
	float GetCapacity() const;

	UFUNCTION(BlueprintCallable)
	void ChangeBy(const float InValue);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemainsChange, float, float);
	FOnRemainsChange OnRemainsChange;

protected:
	UPROPERTY(EditAnywhere)
	float Remains = 1.f;

	UPROPERTY(EditAnywhere)
	float Capacity = 1.f;

};