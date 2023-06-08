#pragma once

#include "Restart.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWORLDINTHESKIES_API URestartComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UCheckpointComponent* CheckpointComponent = nullptr;
};