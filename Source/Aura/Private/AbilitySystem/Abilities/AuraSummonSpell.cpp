// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraSummonSpell.h"


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
		FVector SpawnPos = Pos + Dir * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(
			Hit,
			SpawnPos + FVector(0.f, 0.f, 400.f),
			SpawnPos - FVector(0.f, 0.f, 400.f),
			ECC_Visibility);

		if (Hit.bBlockingHit)
		{
			SpawnPos = Hit.ImpactPoint;
		}
		
		SpawnLocations.Add(SpawnPos);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonSpell::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
