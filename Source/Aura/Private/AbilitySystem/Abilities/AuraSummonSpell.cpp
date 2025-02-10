// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraSummonSpell.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonSpell::GetSpawnLocations()
{
	const FVector Fwd = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Pos = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpreadAngle / MinionCount;
	
	const FVector LSpread = Fwd.RotateAngleAxis(-SpreadAngle / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < MinionCount; i++)
	{
		const FVector Dir = LSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector SpawnPos = Pos + Dir * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(SpawnPos);
		
		DrawDebugSphere(
			GetWorld(),
			SpawnPos,
			18.f,
			12,
			FColor::Blue,
			false,
			3.f);
		
		UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			Pos,
			Pos + Dir * MaxSpawnDistance,
			4.f,
			FLinearColor::Green,
			3.f);

		DrawDebugSphere(
			GetWorld(),
			Pos + Dir * MinSpawnDistance,
			5.f,
			12,
			FColor::Red,
			false,
			3.f);

		DrawDebugSphere(
			GetWorld(),
			Pos + Dir * MaxSpawnDistance,
			5.f,
			12,
			FColor::Red,
			false,
			3.f);
	}

	return SpawnLocations;
}
