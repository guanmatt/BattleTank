// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank> (UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
    //plays effects
    Super::HandleDestruction();
    Destroy();
}
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!PlayerPawn||ReturnDistanceToPlayer()>FireRange)
    {
        return;
    }
    RotateTurret(PlayerPawn->GetActorLocation());

}

void APawnTurret::CheckFireCondition()
{
    // If player == null || is dead then bail
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }
    // If player is in range THEN fire
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        //Fire
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

