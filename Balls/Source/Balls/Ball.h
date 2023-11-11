// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class BALLS_API ABall : public AActor
{
    GENERATED_BODY()

public:

    ABall();

public:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
    virtual void Tick(float deltaTime) override;

protected:

    UFUNCTION()
    void OnHitCallback(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

    void StartSpawnCooldownTimer();

    void BindToHitEvents();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    class UStaticMeshComponent* RootMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    TSubclassOf<AActor> ActorClassToSpawnOnImpact;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    float SpawnCircleRadius = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    uint8 SpawnCount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    float SpawnCooldownSeconds = .25f;

protected:

    FTimerHandle SpawnCooldownTimer;
};
