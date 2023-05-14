#pragma once

#include "PaperCharacter.h"

#include "Jumper.generated.h"

UCLASS()
class AWORLDINTHESKIES_API AJumper : public APaperCharacter
{
	GENERATED_BODY()
public:
	AJumper(const FObjectInitializer& InObjectInitializer);

	void Tick(const float InDeltaTime) override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere)
	class UBreathingComponent* BreathingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UOxygenComponent* OxygenComponent = nullptr;

	void HandleOxygenRemainsChange(const float OldValue, const float NewValue);

};