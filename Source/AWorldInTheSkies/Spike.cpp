#include "Spike.h"
#include "Health.h"

USpikeComponent::USpikeComponent()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetGenerateOverlapEvents(true);
}

void USpikeComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	Owner->OnActorBeginOverlap.AddDynamic(this, &USpikeComponent::OnBeginOverlap);
	Owner->OnActorEndOverlap.AddDynamic(this, &USpikeComponent::OnEndOverlap);
}

void USpikeComponent::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	OnComponentBeginOverlap.RemoveAll(this);
	OnComponentEndOverlap.RemoveAll(this);

	Super::EndPlay(InEndPlayReason);
}

void USpikeComponent::OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!IsValid(InOtherActor))
	{
		return;
	}

	UHealthComponent* HealthComponent = InOtherActor->FindComponentByClass<UHealthComponent>();
	if (!IsValid(HealthComponent))
	{
		return;
	}

	HealthComponent->ChangeBy(-Damage);
}

void USpikeComponent::OnEndOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (!IsValid(InOtherActor))
	{
		return;
	}
}