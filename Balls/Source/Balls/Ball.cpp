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
    
    RootMeshComponent->OnComponentHit.AddDynamic(this, &ABall::OnHitCallback);
}

void ABall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABall::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    FActorSpawnParameters spawnParams;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    const float dividedAngle = (2 * UE_PI) / SpawnCount;

    const FVector& circleUpVector = Hit.ImpactNormal;
    const FVector& circleLocation = Hit.ImpactPoint;

    const FVector& circleForwardVector = FRotationMatrix::MakeFromZ(circleUpVector).GetUnitAxis(EAxis::X);

    for (uint8 i = 0; i < SpawnCount; i++)
    {
        const float rotationAngle = dividedAngle * i;

        const FVector& indexForwardVector = circleForwardVector.RotateAngleAxisRad(rotationAngle, circleUpVector);

        const FVector& indexSpawnLocation = circleLocation + (indexForwardVector * SpawnCircleRadius);

        GetWorld()->SpawnActor<AActor>(ActorClassToSpawnOnImpact, indexSpawnLocation, FRotator::ZeroRotator, spawnParams);
    }
}
