#pragma once

#include "Components/PrimitiveComponent.h"

#include "Checkpoint.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API UCheckpointComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	UCheckpointComponent();

	UPROPERTY(EditAnywhere)
	bool Active = true;

	UPROPERTY(EditAnywhere)
	FVector RestartPosition = FVector::Zero();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

	UFUNCTION()
	virtual void OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

	UFUNCTION()
	virtual void OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

};