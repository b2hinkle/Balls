// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = true;

    RootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = RootMeshComponent;

    RootMeshComponent->BodyInstance.bSimulatePhysics = true;
    RootMeshComponent->BodyInstance.bNotifyRigidBodyCollision = true;
}

void ABall::BeginPlay()
{
    Super::BeginPlay();

    BindToHitEvents();
}

void ABall::EndPlay(const EEndPlayReason::Type endPlayReason)
{
    Super::EndPlay(endPlayReason);

    RootMeshComponent->OnComponentHit.RemoveAll(this);
}

void ABall::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void ABall::OnHitCallback(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
    if (otherActor->IsA<ThisClass>())
    {
        return;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    const float dividedAngle = (2 * UE_PI) / SpawnCount;

    const FVector& circleUpVector = hit.ImpactNormal;
    const FVector& circleLocation = hit.ImpactPoint;

    const FVector& circleForwardVector = FRotationMatrix::MakeFromZ(circleUpVector).GetUnitAxis(EAxis::X);

    for (uint8 i = 0; i < SpawnCount; i++)
    {
        const float rotationAngle = dividedAngle * i;

        const FVector& indexForwardVector = circleForwardVector.RotateAngleAxisRad(rotationAngle, circleUpVector);

        const FVector& indexSpawnLocation = circleLocation + (indexForwardVector * SpawnCircleRadius);

        GetWorld()->SpawnActor<AActor>(ActorClassToSpawnOnImpact, indexSpawnLocation, FRotator::ZeroRotator, spawnParams);
    }

    StartSpawnCooldownTimer();

    RootMeshComponent->OnComponentHit.RemoveAll(this);

#if 0 // Uncomment if we know it's not expensive to frequently change this.
    RootMeshComponent->SetNotifyRigidBodyCollision(false);
#endif // 0
}

void ABall::StartSpawnCooldownTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        SpawnCooldownTimer,
        FTimerDelegate::CreateUObject(this, &ThisClass::BindToHitEvents),
        SpawnCooldownSeconds,
        false);
}

void ABall::BindToHitEvents()
{
    if (RootMeshComponent->OnComponentHit.IsAlreadyBound(this, &ABall::OnHitCallback) == false)
    {
#if 0 // Uncomment if we know it's not expensive to frequently change this.
        RootMeshComponent->SetNotifyRigidBodyCollision(true);
#endif // 0
        RootMeshComponent->OnComponentHit.AddDynamic(this, &ABall::OnHitCallback);
    }
}
