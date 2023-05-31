#pragma once

#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"

#include "Jumper.generated.h"

UCLASS(config = Game)
class AWORLDINTHESKIES_API AJumper : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* RunningFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* FallingFlipbook;

public:
	AJumper(const FObjectInitializer& InObjectInitializer);

	void Tick(const float InDeltaTime) override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	class UBreathingComponent* BreathingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UOxygenComponent* OxygenComponent = nullptr;

	void HandleOxygenRemainsChange(const float OldValue, const float NewValue);

private:
	void AddInputMappingContext();
	void CreateBreathingWidget();
	void Move(const FInputActionValue& Value);
	UPaperFlipbook* PickProperFlipbook();
	void UpdateAnimation();
	void UpdateControlRotation();
};