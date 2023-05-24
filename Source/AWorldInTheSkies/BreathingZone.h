#pragma once

#include "Components/PrimitiveComponent.h"

#include "BreathingZone.generated.h"

class UBreathingComponent;

class AWORLDINTHESKIES_API IBreathingZone
{
public:
	virtual ~IBreathingZone() = default;
protected:
	virtual void HandleStartBreathingComponent(UBreathingComponent& InBreathingComponent) = 0;
	virtual void HandleEndBreathingComponent(UBreathingComponent& InBreathingComponent) = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API UBreathingZoneComponent : public UPrimitiveComponent, public IBreathingZone
{
	GENERATED_BODY()
public:
	UBreathingZoneComponent();

	UPROPERTY(EditAnywhere)
	float NewConsumeValue = 10.f;

	float PreviousConsumeValue = 0.f;

	UPROPERTY(EditAnywhere)
	bool bRestorePreviousValueOnEndOverlap = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

	UFUNCTION()
	void OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor);


	void HandleStartBreathingComponent(UBreathingComponent& InBreathingComponent) override;
	void HandleEndBreathingComponent(UBreathingComponent& InBreathingComponent) override;

};