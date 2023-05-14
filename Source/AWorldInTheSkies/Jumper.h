#pragma once

#include "GameFramework/Character.h"

#include "Jumper.generated.h"

UCLASS()
class AJumper : public ACharacter
{
	GENERATED_BODY()
public:
	AJumper(const FObjectInitializer& InObjectInitializer);

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere)
	class UOxygenComponent* OxygenComponent = nullptr;

	void HandleOxygenRemainsChange(const int32 OldValue, const int32 NewValue);
};