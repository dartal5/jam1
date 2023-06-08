#include "Checkpoint.h"
#include "Restart.h"

UCheckpointComponent::UCheckpointComponent()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetGenerateOverlapEvents(true);
}

void UCheckpointComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	Owner->OnActorBeginOverlap.AddDynamic(this, &UCheckpointComponent::OnBeginOverlap);
	Owner->OnActorEndOverlap.AddDynamic(this, &UCheckpointComponent::OnEndOverlap);
}

void UCheckpointComponent::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	OnComponentBeginOverlap.RemoveAll(this);
	OnComponentEndOverlap.RemoveAll(this);

	Super::EndPlay(InEndPlayReason);
}

void UCheckpointComponent::OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!Active || !IsValid(InOtherActor))
	{
		return;
	}

	APawn* OverlappedPawn = Cast<APawn>(InOverlappedActor);
	if (!IsValid(OverlappedPawn) || 
		!IsValid(OverlappedPawn->Controller) || !OverlappedPawn->Controller->IsPlayerController())
	{
		return;
	}

	URestartComponent* RestartComponent = InOtherActor->FindComponentByClass<URestartComponent>();
	if (!IsValid(RestartComponent))
	{
		return;
	}

	Active = false;
	RestartComponent->CheckpointComponent = this;
}

void UCheckpointComponent::OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!IsValid(InOtherActor))
	{
		return;
	}
}