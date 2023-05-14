#pragma once

#include "Delegates/Delegate.h"

#include "Oxygen.generated.h"

UCLASS()
class UOxygenComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void Initialize(const int32 InCapacity, const int32 InRemain);

	UFUNCTION(BlueprintCallable)
	int32 GetRemains() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCapacity() const;

	UFUNCTION(BlueprintCallable)
	void Increase(const int32 InValue);

	UFUNCTION(BlueprintCallable)
	void Decrease(const int32 InValue);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemainsChange, int32, int32);

	FOnRemainsChange OnRemainsChange;

protected:
	UPROPERTY(EditAnywhere)
	int32 Remains = 100;

	UPROPERTY(EditAnywhere)
	int32 Capacity = 100;

};