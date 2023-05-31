#include "BreathingZone.h"

#include "Breathing.h"

UBreathingZoneComponent::UBreathingZoneComponent()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetGenerateOverlapEvents(true);
}

void UBreathingZoneComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	Owner->OnActorBeginOverlap.AddDynamic(this, &UBreathingZoneComponent::OnBeginOverlap);
	Owner->OnActorEndOverlap.AddDynamic(this, &UBreathingZoneComponent::OnEndOverlap);
}

void UBreathingZoneComponent::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	OnComponentBeginOverlap.RemoveAll(this);
	OnComponentEndOverlap.RemoveAll(this);

	Super::EndPlay(InEndPlayReason);
}

void UBreathingZoneComponent::OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!IsValid(InOtherActor))
	{
		return;
	}

	UBreathingComponent* BreatingComponent = InOtherActor->FindComponentByClass<UBreathingComponent>();
	if (!IsValid(BreatingComponent)) 
	{
		return;
	}

	HandleStartBreathingComponent(*BreatingComponent);
}

void UBreathingZoneComponent::OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!IsValid(InOtherActor))
	{
		return;
	}

	UBreathingComponent* BreatingComponent = InOtherActor->FindComponentByClass<UBreathingComponent>();
	if (!IsValid(BreatingComponent))
	{
		return;
	}

	HandleEndBreathingComponent(*BreatingComponent);
}

void UBreathingZoneComponent::HandleStartBreathingComponent(UBreathingComponent& InBreathingComponent)
{
	PreviousConsumeValue = InBreathingComponent.Consumes;
	InBreathingComponent.Consumes = NewConsumeValue;
}

void UBreathingZoneComponent::HandleEndBreathingComponent(UBreathingComponent& InBreathingComponent)
{
	if (bRestorePreviousValueOnEndOverlap)
	{
		InBreathingComponent.Consumes = PreviousConsumeValue;
	}
}
