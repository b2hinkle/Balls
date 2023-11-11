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
    // Sets default values for this actor's properties
    ABall();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    class UStaticMeshComponent* RootMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    TSubclassOf<AActor> ActorClassToSpawnOnImpact;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    float SpawnCircleRadius = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balls")
    uint8 SpawnCount = 1;

};
