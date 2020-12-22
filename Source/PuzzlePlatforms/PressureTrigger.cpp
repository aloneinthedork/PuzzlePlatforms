// Fill out your copyright notice in the Description page of Project Settings.


#include "PressureTrigger.h"
#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
APressureTrigger::APressureTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void APressureTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APressureTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APressureTrigger::OnOverlapEnd);
	
}

// Called every frame
void APressureTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressureTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Error, TEXT("Activated pressure plate"));
	for (AMovingPlatform* platform : PlatformsToTrigger) {
		platform->AddActiveTrigger();
	}
}

void APressureTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Error, TEXT("Deactivated pressure plate"));
	for (AMovingPlatform* platform : PlatformsToTrigger) {
		platform->RemoveActiveTrigger();
	}
}
