#pragma once

#include "Components/PrimitiveComponent.h"

#include "Spike.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API USpikeComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	USpikeComponent();

	UPROPERTY(EditAnywhere)
	float Damage = 1.f;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

	UFUNCTION()
	virtual void OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

	UFUNCTION()
	virtual void OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

};